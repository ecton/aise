#pragma once
#include "Aise.h"
#include "Token.h"
#include "Value.h"

namespace Aise {
    class Boolean : public Value
    {
    public:
        Boolean(bool isTemplate, std::shared_ptr<Aise::Token> token);
		Boolean(bool isTemplate, bool value) : Aise::Value(isTemplate), mValue(value) {  }
        virtual ~Boolean() { }
        
        virtual std::string Description();
		virtual int Compare(std::shared_ptr<Value> to);

        std::shared_ptr<Aise::Token> Token() { return mToken; }
        bool Value() { return mValue; }


		virtual Result EvaluateTemplate(std::shared_ptr<Aise::Binding> binding);

    private:
        std::shared_ptr<Aise::Token> mToken;
        bool mValue;
    };
}