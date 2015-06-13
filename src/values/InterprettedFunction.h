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
		InterprettedFunction(bool isTemplate, SymbolPtr name, SExpPtr parameters, SExpPtr body) : Aise::Function(isTemplate), mName(name), mParameters(parameters), mBody(body) { }
        virtual ~InterprettedFunction() { }
        
        virtual std::string Description() { return mName->String(); }
        
        virtual Result Invoke(BindingPtr binding, SExpPtr arguments);

		virtual Result EvaluateTemplate(std::shared_ptr<Aise::Binding> binding);
        
    private:
        SymbolPtr mName;
        SExpPtr mParameters;
        SExpPtr mBody;
    };
}