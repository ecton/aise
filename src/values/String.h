#pragma once
#include "AiseCommon.h"
#include "Token.h"
#include "Value.h"

namespace Aise {
    class String : public Value
    {
    public:
      String(bool isTemplate, std::shared_ptr<Aise::Token> token) : Aise::Value(isTemplate), mToken(token) { mValue = mToken->String(); }
      String(bool isTemplate, std::string value) : Aise::Value(isTemplate), mValue(value) { }
      virtual ~String() { }
        
      virtual std::string Description();
      virtual int Compare(ValuePtr to);
        
      std::shared_ptr<Aise::Token> Token() { return mToken; }
      std::string Value() { return mValue; }

      virtual Result EvaluateTemplate(BindingPtr binding);
    private:
      std::shared_ptr<Aise::Token> mToken;
      std::string mValue;
    };
}
