#pragma once
#include "Aise.h"
#include "Token.h"
#include "Value.h"

namespace Aise {
    class Real : public Value
    {
    public:
        Real(std::shared_ptr<Aise::Token> token) : mToken(token) { mValue = std::stod(mToken->String()); }
        Real(double value) : mValue(value) { }
        virtual ~Real() { }
        
        virtual std::string Description();
        
        std::shared_ptr<Aise::Token> Token() { return mToken; }
        double Value() { return mValue; }
    private:
        std::shared_ptr<Aise::Token> mToken;
        double mValue;
    };
}