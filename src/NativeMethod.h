#pragma once
#include "Aise.h"
#include "Binding.h"
#include "Method.h"
#include "SExp.h"
#include "Result.h"

namespace Aise {
    
    class NativeMethod : public Method
    {
    public:
        class Implementation {
        public:
            Implementation() { }
            virtual ~Implementation() { }
			virtual Result Invoke(BindingPtr binding, SExpPtr sexp) = 0;
        };
        NativeMethod(std::string name, Implementation *impl) : mName(name), mImplementation(impl) { }
        virtual ~NativeMethod() { }

		static void Initialize(BindingPtr binding, std::string name, NativeMethod::Implementation *impl) { binding->Assign(name, ValuePtr(new NativeMethod(name, impl))); }
        
        virtual std::string Description();
		virtual Result Invoke(BindingPtr binding, SExpPtr sexp);
        
        class UnaryMethodImplementation : public Implementation
        {
        public:
            virtual Result Invoke(BindingPtr binding, SExpPtr sexp);
            virtual Result Invoke(BindingPtr binding, ValuePtr arg) = 0;
        };
        
        class VariableArgumentMethodImplementation : public Implementation
        {
        public:
            virtual Result Invoke(BindingPtr binding, SExpPtr sexp);
            virtual Result Invoke(BindingPtr binding, std::vector<ValuePtr> &args) = 0;
        };
        
    private:
        std::string mName;
        Implementation *mImplementation;
    };
}