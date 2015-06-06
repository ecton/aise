#pragma once
#include "Aise.h"
#include "Token.h"
#include "Value.h"

namespace Aise {
    class Integer : public Value
    {
    public:
        Integer(std::shared_ptr<Aise::Token> token) : mToken(token) { mValue = std::stol(mToken->String()); }
        Integer(long value) : mValue(value) { }
        virtual ~Integer() { }
        
        virtual std::string Description();
        
        std::shared_ptr<Aise::Token> Token() { return mToken; }
        long Value() { return mValue; }
    private:
        std::shared_ptr<Aise::Token> mToken;
        long mValue;
    };
}