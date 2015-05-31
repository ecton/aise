#pragma once
#include "Aise.h"
#import "Token.h"

namespace Aise {
    class Symbol : public Value
    {
    public:
        Symbol(Token token);
        virtual ~Symbol();
        
        virtual std::string Description();
        
        Token Token() { return mToken; }
    private:
        Aise::Token mToken;
    };
}