#include "Environment.h"
#include "Tokenizer.h"
#include "SExp.h"
#include "Symbol.h"
#include "Integer.h"
#include "Real.h"
#include "NativeFunction.h"
#include "Boolean.h"

#include <iostream>

#include "Math.h"
#include "Logic.h"

using namespace std;

namespace Aise {
	Environment::Environment()
	{
		mBindingStack.push_back(BindingPtr(new Binding(this)));
        Globals()->Assign("true", ValuePtr(new Boolean(true)));
        Globals()->Assign("false", ValuePtr(new Boolean(false)));
		Math::Initialize(Globals());
        Logic::Initialize(Globals());
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
        return Result("Unknown reference", expression);
    }
    
    Result Environment::Interpret(BindingPtr binding, ValuePtr expression)
    {
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
                
				return Result(ValuePtr(new SExp(left.Value(), right.Value())));
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
		ValuePtr root;
		ValuePtr current;
	};
    
    Result Environment::Parse(shared_ptr<Source> source)
    {
        cout << "Parsing: " << *source->Src() << endl;
        auto tokens = Tokenizer(source);
        vector<SExpStackEntry *> stack;
		ValuePtr main = { 0 };
        
        while (!tokens.EndOfInput()) {
            auto token = tokens.Next();
            if (token->Type() == Token::TYPE_OPEN_PAREN) {
                // Create a new SExp to contain the insides of these parentheses.
				stack.push_back(new SExpStackEntry());
			}
			else if (token->Type() == Token::TYPE_CLOSE_PAREN) {
                if (stack.size() == 0) return Result("Parse Error: Closing parentheses does not have a match.", ValuePtr(new Symbol(token)));
                
				auto terminated = stack[stack.size() - 1];
				stack.pop_back();
				if (stack.size() > 0) {
					auto entry = stack[stack.size() - 1];
					auto insertion = ValuePtr(new SExp(terminated->root, ValuePtr(NULL)));
					auto insertAt = dynamic_pointer_cast<SExp>(entry->current);
					insertAt->ReplaceRight(insertion);
					entry->current = insertion;
				}
				delete terminated;
            } else if (Token::TypeIsLiteral(token->Type())) {
                if (stack.size() == 0) return Result("Parse Error: Literal value not inside of an s-expression.", ValuePtr(new Symbol(token)));
				auto entry = stack[stack.size() - 1];

                ValuePtr literal;
                switch (token->Type()) {
                    case Token::TYPE_INTEGER: {
                        literal = ValuePtr(new Integer(token));
                    } break;
                    case Token::TYPE_REAL: {
                        literal = ValuePtr(new Real(token));
                    } break;
                    case Token::TYPE_IDENTIFIER: {
                        literal = ValuePtr(new Symbol(token));
                    } break;
                    default:
                        return Result("Parse Error: Unknown literal type", ValuePtr(new Symbol(token)));
                }
                ValuePtr newSExp = ValuePtr(new SExp(literal, ValuePtr(NULL)));
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