#include "Environment.h"
#include "Tokenizer.h"
#include "SExp.h"
#include "Symbol.h"

#include <iostream>

using namespace std;

namespace Aise {
	Environment::Environment()
	{
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
        
		return NULL;
	}
    
    ValuePtr Environment::Parse(shared_ptr<Source> source)
    {
        auto tokens = Tokenizer(source);
        vector<ValuePtr> leftStack;
        ValuePtr main;
        
        // (a (b c) d)
        // a
        //  / \  /\
        // b /\
             c-
        while (!tokens.EndOfInput()) {
            auto token = tokens.Next();
            if (token.Type() == Token::TYPE_OPEN_PAREN) {
                // Create a new SExp to contain the insides of these parentheses.
                leftStack.push_back(ValuePtr(NULL));
            } else if (token.Type() == Token::TYPE_CLOSE_PAREN) {
                leftStack.pop_back();
            } else if (token.Type() == Token::TYPE_IDENTIFIER) {
                if (leftStack.size() == 0) throw "TODO: Empty left stack";
                ValuePtr current = leftStack[leftStack.size() - 1];
                ValuePtr newSExp = ValuePtr(new SExp(ValuePtr(new Symbol(token)), ValuePtr(NULL)));
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
        
        cout << main->Description();
        
        return main;
    }
}