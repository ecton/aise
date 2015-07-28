#pragma once
#include "AiseCommon.h"
#include "Token.h"
#include "Value.h"

namespace Aise {
  class Symbol : public Value
  {
  public:
    Symbol(bool isTemplate, std::shared_ptr<Aise::Token> token);
    virtual ~Symbol();
    
    virtual std::string Description();
    virtual int Compare(ValuePtr to);
    
    std::shared_ptr<Aise::Token> Token() { return mToken; }
    std::string String() { return mToken->String(); }

    virtual Result EvaluateTemplate(BindingPtr binding);
  private:
    std::shared_ptr<Aise::Token> mToken;
  };
}