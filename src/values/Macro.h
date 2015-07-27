#pragma once
#include "AiseCommon.h"
#include "Token.h"
#include "Function.h"
#include "SExp.h"
#include "Symbol.h"

namespace Aise {
    class Macro : public Function
    {
    public:
    Macro(bool isTemplate, SymbolPtr name, SExpPtr parameters, SExpPtr body) : Aise::Function(isTemplate), mName(name), mParameters(parameters), mBody(body) { }
    virtual ~Macro() { }
        
        virtual std::string Description() { return mName->String(); }
        
        virtual Result Invoke(BindingPtr binding, SExpPtr arguments);

    virtual Result EvaluateTemplate(BindingPtr binding);
        
    private:
        SymbolPtr mName;
        SExpPtr mParameters;
        SExpPtr mBody;
    };
}