#pragma once
#include "Aise.h"
#include "Token.h"
#include "Method.h"
#include "SExp.h"

namespace Aise {
    class InterprettedMethod : public Method
    {
    public:
        InterprettedMethod(std::shared_ptr<Token> name, SExpPtr arguments, SExpPtr body) : mName(name), mArguments(arguments), mBody(body) { }
        virtual ~InterprettedMethod() { }
        
        virtual std::string Description() { return mName->String(); }
        
        virtual Result Invoke(BindingPtr binding, SExpPtr arguments);
        
    private:
        std::shared_ptr<Aise::Token> mName;
        SExpPtr mArguments;
        SExpPtr mBody;
    };
}