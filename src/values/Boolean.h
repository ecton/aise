#pragma once
#include "Aise.h"
#include "Token.h"
#include "Value.h"

namespace Aise {
    class Boolean : public Value
    {
    public:
        Boolean(std::shared_ptr<Token> token);
        Boolean(bool value) : mValue(value) { }
        virtual ~Boolean() { }
        
        virtual std::string Description();
        
        std::shared_ptr<Aise::Token> Token() { return mToken; }
        bool Value() { return mValue; }
    private:
        std::shared_ptr<Aise::Token> mToken;
        bool mValue;
    };
}