#pragma once
#include "Aise.h"
#include "Token.h"
#include "Function.h"
#include "SExp.h"
#include "Symbol.h"

namespace Aise {
    class InterprettedFunction : public Function
    {
    public:
		InterprettedFunction(SymbolPtr name, SExpPtr parameters, SExpPtr body) : mName(name), mParameters(parameters), mBody(body) { }
        virtual ~InterprettedFunction() { }
        
        virtual std::string Description() { return mName->String(); }
        
        virtual Result Invoke(BindingPtr binding, SExpPtr arguments);
        
    private:
        SymbolPtr mName;
        SExpPtr mParameters;
        SExpPtr mBody;
    };
}