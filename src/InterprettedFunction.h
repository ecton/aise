#pragma once
#include "Aise.h"
#include "Token.h"
#include "Function.h"
#include "SExp.h"

namespace Aise {
    class InterprettedFunction : public Function
    {
    public:
        InterprettedFunction(std::shared_ptr<Token> name, SExpPtr arguments, SExpPtr body) : mName(name), mArguments(arguments), mBody(body) { }
        virtual ~InterprettedFunction() { }
        
        virtual std::string Description() { return mName->String(); }
        
        virtual Result Invoke(BindingPtr binding, SExpPtr arguments);
        
    private:
        std::shared_ptr<Aise::Token> mName;
        SExpPtr mArguments;
        SExpPtr mBody;
    };
}