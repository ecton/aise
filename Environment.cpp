#include "Environment.h"
#include "Tokenizer.h"
#include "SExp.h"
#include "Symbol.h"
#include "Integer.h"
#include "Real.h"
#include "NativeMethod.h"

#include <iostream>

using namespace std;

namespace Aise {
    class PlusMethod : public NativeMethod::Implementation
    {
    public:
        PlusMethod() { }
        virtual ValuePtr Invoke(Environment *env, SExpPtr sexp) {
            bool isReal = false;
            long intValue = 0;
            double realValue = 0;
            SExpPtr current = dynamic_pointer_cast<SExp>(sexp->Right());
            if (!current) throw "Unknown exp to plus";
            
            while (current) {
                if (auto integer = dynamic_pointer_cast<Integer>(current->Left())) {
                    if (isReal) {
                        realValue += integer->Value();
                    } else {
                        intValue += integer->Value();
                    }
                } else if (auto real = dynamic_pointer_cast<Real>(current->Left())) {
                    if (!isReal) {
                        isReal = true;
                        realValue = intValue;
                    }
                    realValue += real->Value();
                } else {
                    throw "Unknown lhs to plus";
                }
                current = dynamic_pointer_cast<SExp>(current->Right());
            }
            if (isReal) {
                return ValuePtr(new Real(realValue));
            } else {
                return ValuePtr(new Integer(intValue));
            }
        }
    };
    
    
	Environment::Environment()
	{
        mGlobals.Assign("plus", ValuePtr(new NativeMethod("plus", new PlusMethod())));
	}


	Environment::~Environment()
	{
	}

	void Environment::AddSource(string name, const std::string &src)
	{
		mSources[name] = shared_ptr<Source>(new Source(name, StringPtr(new string(src))));
	}

    ValuePtr Environment::Evaluate(const std::string &main)
	{
        auto mainSource = shared_ptr<Source>(new Source("main", StringPtr(new string(main))));
        
        ValuePtr program = Parse(mainSource);
        
        return Interpret(program);
	}
    
    ValuePtr Environment::Interpret(ValuePtr expression)
    {
        auto sexp = dynamic_pointer_cast<SExp>(expression);
        if (sexp) {
            // Reduce the sexp by evaluating it
            auto lval = dynamic_pointer_cast<Symbol>(sexp->Left());
            if (!lval) throw "Unknown lval";
            
            auto method = dynamic_pointer_cast<NativeMethod>(mGlobals.Get(lval->Token()->String()));
            
            if (method) {
                return method->Invoke(this, sexp);
            } else {
                throw "Unknown result from binding lookup.";
            }
        } else {
            // Already a fundamental type, that's the result
            return expression;
        }
    }
    
    ValuePtr Environment::Parse(shared_ptr<Source> source)
    {
        cout << "Parsing: " << *source->Src() << endl;
        auto tokens = Tokenizer(source);
        vector<ValuePtr> leftStack;
        ValuePtr main;
        
        while (!tokens.EndOfInput()) {
            auto token = tokens.Next();
            if (token->Type() == Token::TYPE_OPEN_PAREN) {
                // Create a new SExp to contain the insides of these parentheses.
                leftStack.push_back(ValuePtr(NULL));
            } else if (token->Type() == Token::TYPE_CLOSE_PAREN) {
                leftStack.pop_back();
            } else if (Token::TypeIsLiteral(token->Type())) {
                if (leftStack.size() == 0) throw "TODO: Empty left stack";
                ValuePtr current = leftStack[leftStack.size() - 1];
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
                        throw "Unhandled token type.";
                }
                ValuePtr newSExp = ValuePtr(new SExp(literal, ValuePtr(NULL)));
                if (current == NULL) {
                    if (main != NULL) throw "TODO: Already have a main entry";
                    main = newSExp;
                } else {
                    auto sexp = static_pointer_cast<SExp>(current);
                    sexp->ReplaceRight(newSExp);
                }
                leftStack[leftStack.size() - 1] = newSExp;
            }
        }
        
        cout << "Reproduced Tree: " << main->Description() << endl;
        
        return main;
    }
}