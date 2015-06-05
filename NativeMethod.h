#pragma once
#include "Aise.h"
#include "Binding.h"
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
			virtual ValuePtr Invoke(BindingPtr binding, SExpPtr sexp) = 0;
        };
        NativeMethod(std::string name, Implementation *impl) : mName(name), mImplementation(impl) { }
        virtual ~NativeMethod() { }

		static void Initialize(BindingPtr binding, std::string name, NativeMethod::Implementation *impl) { binding->Assign(name, ValuePtr(new NativeMethod(name, impl))); }
        
        virtual std::string Description();
		ValuePtr Invoke(BindingPtr binding, SExpPtr sexp);
    private:
        std::string mName;
        Implementation *mImplementation;
    };
}