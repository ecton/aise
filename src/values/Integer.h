#pragma once
#include "AiseCommon.h"
#include "Token.h"
#include "Value.h"

namespace Aise {
    class Integer : public Value
    {
    public:
        Integer(bool isTemplate, std::shared_ptr<Aise::Token> token) : Aise::Value(isTemplate), mToken(token) { mValue = std::stol(mToken->String()); }
        Integer(bool isTemplate, long value) : Aise::Value(isTemplate), mValue(value) { }
        virtual ~Integer() { }
        
		virtual std::string Description();
		virtual int Compare(ValuePtr to);
        
        std::shared_ptr<Aise::Token> Token() { return mToken; }
        long Value() { return mValue; }

		virtual Result EvaluateTemplate(BindingPtr binding);
    private:
        std::shared_ptr<Aise::Token> mToken;
        long mValue;
    };
}