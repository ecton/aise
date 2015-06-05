#pragma once
#include "Aise.h"
#include "Environment.h"
#include "Value.h"
#include "SExp.h"

namespace Aise {
    
    class NativeMethod : public Value
    {
    public:
        class Implementation {
        public:
            Implementation() { }
            virtual ~Implementation() { }
            virtual ValuePtr Invoke(Environment *env, SExpPtr sexp) = 0;
        };
        NativeMethod(std::string name, Implementation *impl) : mName(name), mImplementation(impl) { }
        virtual ~NativeMethod() { }
        
        virtual std::string Description();
        ValuePtr Invoke(Environment *env, SExpPtr sexp) { return mImplementation->Invoke(env, sexp); }
    private:
        std::string mName;
        Implementation *mImplementation;
    };
}