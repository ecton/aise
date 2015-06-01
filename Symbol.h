#pragma once
#include "Aise.h"
#import "Token.h"
#include "Value.h"

namespace Aise {
    class Symbol : public Value
    {
    public:
        Symbol(std::shared_ptr<Token> token);
        virtual ~Symbol();
        
        virtual std::string Description();
        
        std::shared_ptr<Token> Token() { return mToken; }
    private:
        std::shared_ptr<Aise::Token> mToken;
    };
}