#pragma once
#include "AiseCommon.h"
#include "Binding.h"
#include "Function.h"
#include "SExp.h"
#include "Result.h"

namespace Aise {
  
  class NativeFunction : public Function
  {
  public:
    class Implementation {
    public:
      Implementation() { }
      virtual ~Implementation() { }
      virtual Result Invoke(BindingPtr binding, SExpPtr sexp) = 0;
    };
    NativeFunction(std::string name, Implementation *impl) : Aise::Function(false), mName(name), mImplementation(impl) { }
    virtual ~NativeFunction() { }

    static void Initialize(BindingPtr binding, std::string name, NativeFunction::Implementation *impl) { binding->Assign(name, ValuePtr(new NativeFunction(name, impl))); }
    
    virtual std::string Description();
    virtual Result Invoke(BindingPtr binding, SExpPtr sexp);
    
    class UnaryFunctionImplementation : public Implementation
    {
    public:
      virtual Result Invoke(BindingPtr binding, SExpPtr sexp);
      virtual Result Invoke(BindingPtr binding, ValuePtr arg) = 0;
    };
    
    class VariableArgumentFunctionImplementation : public Implementation
    {
    public:
      virtual Result Invoke(BindingPtr binding, SExpPtr sexp);
      virtual Result Invoke(BindingPtr binding, std::vector<ValuePtr> &args) = 0;
    };

    virtual Result EvaluateTemplate(BindingPtr binding);
    
  private:
    std::string mName;
    Implementation *mImplementation;
  };
}