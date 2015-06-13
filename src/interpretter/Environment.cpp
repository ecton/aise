#include "Environment.h"
#include "Tokenizer.h"
#include "SExp.h"
#include "Symbol.h"
#include "Integer.h"
#include "Real.h"
#include "NativeFunction.h"
#include "Boolean.h"

#include <iostream>

#include "Arithmetic.h"
#include "Logic.h"
#include "Functions.h"
#include "Flow.h"

using namespace std;

namespace Aise {
	Environment::Environment()
	{
		mBindingStack.push_back(BindingPtr(new Binding(this)));
        Globals()->Assign("true", ValuePtr(new Boolean(false, true)));
        Globals()->Assign("false", ValuePtr(new Boolean(false, false)));
		Arithmetic::Initialize(Globals());
        Logic::Initialize(Globals());
		Functions::Initialize(Globals());
		Flow::Initialize(Globals());
	}

	Environment::~Environment()
	{
	}
    
    ValuePtr Environment::TrueValue() {
        return Globals()->Get("true");
    }
    
    ValuePtr Environment::FalseValue() {
        return Globals()->Get("false");
    }

	void Environment::AddSource(string name, const std::string &src)
	{
		mSources[name] = shared_ptr<Source>(new Source(name, StringPtr(new string(src))));
	}

	BindingPtr Environment::EnterBinding() {
		BindingPtr newBinding = BindingPtr(new Binding(this));
		mBindingStack.push_back(newBinding);
		return newBinding;
	}

	void Environment::ExitBinding() {
		mBindingStack.pop_back();
	}

    Result Environment::Evaluate(const std::string &main)
	{
        auto mainSource = shared_ptr<Source>(new Source("main", StringPtr(new string(main))));
        
        Result program = Parse(mainSource);
        if (program.Error()) return program;
        
        return Interpret(Globals(), program.Value());
	}
    
    Result Environment::Invoke(BindingPtr binding, ValuePtr lookup, SExpPtr expression)
    {
        auto method = dynamic_pointer_cast<Function>(lookup);
        if (method) {
            return method->Invoke(binding, expression);
        }
        return Result(lookup);
    }
    
    Result Environment::LookupAndInvoke(BindingPtr binding, shared_ptr<Symbol> symbol, SExpPtr expression)
    {
        auto value = binding->Get(symbol->String());
        if (value) {
            return Invoke(binding, value, expression);
        }
        if (binding != Globals()) {
            value = Globals()->Get(symbol->String());
            if (value) {
                return Invoke(binding, value, expression);
            }
        }
        return Result("Unknown reference", expression);
    }
    
    Result Environment::Lookup(BindingPtr binding, shared_ptr<Symbol> symbol, ValuePtr expression)
    {
        auto value = binding->Get(symbol->String());
        if (value) {
            return Result(value);
        }
        if (binding != Globals()) {
            value = Globals()->Get(symbol->String());
            if (value) {
                return Result(value);
            }
        }
        return Result(dynamic_pointer_cast<Value>(symbol));
    }
    
    Result Environment::Interpret(BindingPtr binding, ValuePtr expression)
    {
		if (!expression) return expression;

		// If the expression is a template, evaluate the template
		if (expression->IsTemplate()) {
			return expression->EvaluateTemplate(binding);
		}

        auto sexp = dynamic_pointer_cast<SExp>(expression);
        if (sexp) {
            // Reduce the sexp by evaluating it
			// If it's another sexp, we should evaluate it and replace it
			auto innerSexp = dynamic_pointer_cast<SExp>(sexp->Left());
			if (innerSexp) {
                auto left = Interpret(binding, sexp->Left());
                if (left.Error()) return left;
                
                auto right = Interpret(binding, sexp->Right());
                if (right.Error()) return right;
                
				return Result(ValuePtr(new SExp(false, left.Value(), right.Value())));
			}
			
            auto lval = dynamic_pointer_cast<Symbol>(sexp->Left());
			// If it's not a method, we can't simplify further
			if (!lval) return Result(expression);
            
            return LookupAndInvoke(binding, lval, sexp);
        } else if (auto symbol = dynamic_pointer_cast<Symbol>(expression)) {
            return Lookup(binding, symbol, expression);
        } else {
            // Already a fundamental type, that's the result
            return Result(expression);
        }
    }

	class SExpStackEntry
	{
	public:
		SExpStackEntry(bool tpl) : isTemplate(tpl) {}
		ValuePtr root;
		ValuePtr current;
		bool isTemplate;
	};
    
    Result Environment::Parse(shared_ptr<Source> source)
    {
        cout << "Parsing: " << *source->Src() << endl;
        auto tokens = Tokenizer(source);
        vector<SExpStackEntry *> stack;
		ValuePtr main = { 0 };
		bool overrideNextTemplateFlag = false;
		bool nextIsTemplate = false;
        
        while (!tokens.EndOfInput()) {
			bool thisIsTemplate = false;
			if (overrideNextTemplateFlag) {
				overrideNextTemplateFlag = false;
				thisIsTemplate = nextIsTemplate;
			}
			else if (stack.size() > 0) {
				thisIsTemplate = stack[stack.size() - 1]->isTemplate;
			} 

            auto token = tokens.Next();
            if (token->Type() == Token::TYPE_OPEN_PAREN) {
                // Create a new SExp to contain the insides of these parentheses.
				stack.push_back(new SExpStackEntry(thisIsTemplate));
			}
			else if (token->Type() == Token::TYPE_CLOSE_PAREN) {
				if (stack.size() == 0) return Result("Parse Error: Closing parentheses does not have a match.", ValuePtr(new Symbol(thisIsTemplate, token)));

				auto terminated = stack[stack.size() - 1];
				stack.pop_back();
				if (stack.size() > 0) {
					auto entry = stack[stack.size() - 1];
					// Special case, if we never created any root, we have an empty SExpression, and so we should insert an empty one rather than NULL
					if (!terminated->root) terminated->root = ValuePtr(new SExp(thisIsTemplate, NULL, NULL));
					auto insertion = ValuePtr(new SExp(thisIsTemplate, terminated->root, ValuePtr(NULL)));
					auto insertAt = dynamic_pointer_cast<SExp>(entry->current);
					insertAt->ReplaceRight(insertion);
					entry->current = insertion;
				}
				delete terminated;
			}
			else if (token->Type() == Token::TYPE_BACKTICK) {
				// Next token should be treated as a template
				nextIsTemplate = true;
				overrideNextTemplateFlag = true;
			}
			else if (token->Type() == Token::TYPE_COMMA) {
				// Next token should be treated as a regular token
				nextIsTemplate = false;
				overrideNextTemplateFlag = true;

            } else if (Token::TypeIsLiteral(token->Type())) {
                if (stack.size() == 0) return Result("Parse Error: Literal value not inside of an s-expression.", ValuePtr(new Symbol(thisIsTemplate, token)));
				auto entry = stack[stack.size() - 1];

                ValuePtr literal;
                switch (token->Type()) {
                    case Token::TYPE_INTEGER: {
                        literal = ValuePtr(new Integer(thisIsTemplate, token));
                    } break;
                    case Token::TYPE_REAL: {
                        literal = ValuePtr(new Real(thisIsTemplate, token));
                    } break;
                    case Token::TYPE_IDENTIFIER: {
                        literal = ValuePtr(new Symbol(thisIsTemplate, token));
                    } break;
                    default:
                        return Result("Parse Error: Unknown literal type", ValuePtr(new Symbol(thisIsTemplate, token)));
                }
                ValuePtr newSExp = ValuePtr(new SExp(thisIsTemplate, literal, ValuePtr(NULL)));
				if (entry->root == NULL) {
					entry->root = newSExp;
					if (main == NULL) {
						main = newSExp;
					}
				}
				else {
					auto current = dynamic_pointer_cast<SExp>(entry->current);
					current->ReplaceRight(newSExp);
				}
				entry->current = newSExp;
            }
        }
        
        cout << "Reproduced Tree: " << main->Description() << endl;
        
        return main;
    }
}