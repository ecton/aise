#pragma once
#include "Aise.h"
#include "Token.h"
#include "Value.h"

namespace Aise {
    class Symbol : public Value
    {
    public:
        Symbol(std::shared_ptr<Token> token);
        virtual ~Symbol();
        
        virtual std::string Description();
        
        std::shared_ptr<Token> Token() { return mToken; }
        std::string String() { return mToken->String(); }
    private:
        std::shared_ptr<Aise::Token> mToken;
    };
	typedef std::shared_ptr<Symbol> SymbolPtr;
}