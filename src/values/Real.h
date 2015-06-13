#pragma once
#include "Aise.h"
#include "Token.h"
#include "Value.h"

namespace Aise {
    class Real : public Value
    {
    public:
        Real(bool isTemplate, std::shared_ptr<Aise::Token> token) : Aise::Value(isTemplate), mToken(token) { mValue = std::stod(mToken->String()); }
        Real(bool isTemplate, double value) : Aise::Value(isTemplate), mValue(value) { }
        virtual ~Real() { }
        
		virtual std::string Description();
		virtual int Compare(std::shared_ptr<Value> to);
        
        std::shared_ptr<Aise::Token> Token() { return mToken; }
        double Value() { return mValue; }

		virtual Result EvaluateTemplate(std::shared_ptr<Aise::Binding> binding);
    private:
        std::shared_ptr<Aise::Token> mToken;
        double mValue;
    };
}