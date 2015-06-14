#include "Environment.h"
#include "Tokenizer.h"
#include "SExp.h"
#include "Symbol.h"
#include "Integer.h"
#include "Real.h"
#include "NativeFunction.h"
#include "Boolean.h"
#include "List.h"

#include <iostream>

#include "Arithmetic.h"
#include "Logic.h"
#include "Functions.h"
#include "Flow.h"

#define CATCH_CONFIG_RUNNER
#include "Catch.h"

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


	int Environment::UnitTest()
	{
		return Catch::Session().run();
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
                
                return SExp::Create(false, left.Value(), right.Value());
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

	Result Environment::ParseValue(Tokenizer &tokens, bool isTemplate)
	{
		// Evaluate any modifiers if we have them
		bool doneWithModifiers = false;
		while (!tokens.EndOfInput() && !doneWithModifiers) {
			switch (tokens.Peek()->Type())
			{
			case Token::TYPE_COMMA: tokens.Next();  isTemplate = false; break;
			case Token::TYPE_BACKTICK: tokens.Next();  isTemplate = true; break;
			default:
				doneWithModifiers = true;
				break;
			}
		}
		if (tokens.EndOfInput()) return Result("Unexpected end of input", ValuePtr(NULL));

		switch (tokens.Peek()->Type())
		{
			case Token::TYPE_OPEN_PAREN: {
				return ParseSExp(tokens, isTemplate);
			} break;
			case Token::TYPE_OPEN_BRACKET: {
				return ParseList(tokens, isTemplate);
			} break;
			case Token::TYPE_INTEGER: {
				return ValuePtr(new Integer(isTemplate, tokens.Next()));
			} break;
			case Token::TYPE_REAL: {
				return ValuePtr(new Real(isTemplate, tokens.Next()));
			} break;
			case Token::TYPE_IDENTIFIER: {
				return ValuePtr(new Symbol(isTemplate, tokens.Next()));
			} break;
			default:
				return Result("Unexpected token", ValuePtr(NULL));
		}
	}

	Result Environment::ParseSExp(Tokenizer &tokens, bool isTemplate)
	{
		if (tokens.EndOfInput()) return Result("Unexpected end of input", ValuePtr(NULL));
		auto openParen = tokens.Next();
		if (openParen->Type() != Token::TYPE_OPEN_PAREN) return Result("Expected SExpression start", ValuePtr(NULL));
		if (tokens.EndOfInput()) return Result("Expected end paren or SExpression body", ValuePtr(NULL));

		// First edge case is handling an empty SExp -- () is transformed into (NULL NULL)
		if (tokens.Peek()->Type() == Token::TYPE_CLOSE_PAREN) {
			tokens.Next();
			return SExp::Create(isTemplate, ValuePtr(NULL), ValuePtr(NULL));;
		}

		auto leftResult = ParseValue(tokens, isTemplate);
		if (leftResult.Error()) return leftResult;
		SExpPtr top = SExpPtr(new SExp(isTemplate, leftResult.Value(), ValuePtr(NULL)));
		auto current = top;

		// Iterate until we run into the close paren, expanding the tree such that (a b c) is (a (b (c NULL)))
		while (!tokens.EndOfInput() && tokens.Peek()->Type() != Token::TYPE_CLOSE_PAREN) {
			auto rightResult = ParseValue(tokens, isTemplate);
			if (rightResult.Error()) return rightResult;
			auto next = SExpPtr(new SExp(isTemplate, rightResult.Value(), ValuePtr(NULL)));
			current->ReplaceRight(next);
			current = next;
		}

		if (tokens.EndOfInput()) return Result("Unexpected end of input", ValuePtr(NULL));
		auto closeParen = tokens.Next();
		if (closeParen->Type() != Token::TYPE_CLOSE_PAREN) return Result("Expected )", ValuePtr(NULL));
		return dynamic_pointer_cast<Value>(top);
	}

	Result Environment::ParseList(Tokenizer &tokens, bool isTemplate)
	{
		if (tokens.EndOfInput()) return Result("Unexpected end of input", ValuePtr(NULL));
		auto openBracket = tokens.Next();
		if (openBracket->Type() != Token::TYPE_OPEN_BRACKET) return Result("Expected list start", ValuePtr(NULL));
		if (tokens.EndOfInput()) return Result("Expected end bracket or expression list", ValuePtr(NULL));

		auto list = new List(isTemplate);

		while (!tokens.EndOfInput() && tokens.Peek()->Type() != Token::TYPE_CLOSE_BRACKET) {
			auto result = ParseValue(tokens, isTemplate);
			if (result.Error()) return result;

			list->Push(result.Value());

			if (tokens.Peek()->Type() == Token::TYPE_COMMA) {
				tokens.Next();
			}
			else if (tokens.Peek()->Type() != Token::TYPE_CLOSE_BRACKET) {
				return Result("Expected end bracket or comma", ValuePtr(NULL));
			}
		}

		if (tokens.EndOfInput()) return Result("Unexpected end of input", ValuePtr(NULL));
		auto closeBracket = tokens.Next();
		if (closeBracket->Type() != Token::TYPE_CLOSE_BRACKET) return Result("Expected )", ValuePtr(NULL));
		return ValuePtr(list);
	}
    
    Result Environment::Parse(shared_ptr<Source> source)
    {
        cout << "Parsing: " << *source->Src() << endl;
        auto tokens = Tokenizer(source);

		auto result = ParseSExp(tokens, false);
		if (!result.Error()) {
			if (!tokens.EndOfInput()) return Result("Expected end of file", ValuePtr(NULL));
			cout << "Reproduced Tree: " << result.Value()->Description() << endl;
		}
		return result;
    }
}