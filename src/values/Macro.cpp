//
//  InterprettedFunction.cpp
//  aise
//
//  Created by Jonathan Johnson on 6/5/15.
//
//

#include "Macro.h"
#include "Environment.h"
#include "Binding.h"

using namespace std;

namespace Aise 
{
  class MacroBinding : public Binding
  {
  private:
    BindingPtr mWrappedBinding;
  public:
    MacroBinding(BindingPtr binding) : Binding(binding->Environment()), mWrappedBinding(binding) { }

    virtual ValuePtr Get(std::string name)
    {
      ValuePtr result = Binding::Get(name);
      if (result) return result;

      return mWrappedBinding->Get(name);
    }
  };

  Result Macro::Invoke(BindingPtr binding, SExpPtr arguments)
  {
    BindingPtr methodBinding = BindingPtr(dynamic_cast<Binding *>(new MacroBinding(binding)));

    // Loop over the parameters and try to extract arguments
    auto currentParameterContainer = mParameters;
    auto currentArgumentContainer = dynamic_pointer_cast<SExp>(arguments->Right());
    
    // Check for the special case of no parameters requiring no actual SExp
    if (!currentParameterContainer->IsEmpty()) {
      while (currentParameterContainer) {
        auto name = dynamic_pointer_cast<Symbol>(currentParameterContainer->Left());
        auto result = binding->Interpret(currentArgumentContainer->Left());
        if (result.Error()) return result;

        methodBinding->Assign(name->String(), result.Value());

        auto nextParameterContainer = dynamic_pointer_cast<SExp>(currentParameterContainer->Right());
        auto nextArgumentContainer = dynamic_pointer_cast<SExp>(currentArgumentContainer->Right());
        if (nextParameterContainer && !nextArgumentContainer) return Result("Not enough arguments", currentArgumentContainer);
        if (nextArgumentContainer && !nextParameterContainer) return Result("Too many arguments", currentArgumentContainer);
        currentParameterContainer = nextParameterContainer;
        currentArgumentContainer = nextArgumentContainer;
      }
    }
    else {
      if (currentArgumentContainer && !currentArgumentContainer->IsEmpty()) {
        return Result("Function expects no arguments, but received arguments", arguments);
      }
    }

    Result evaluation = methodBinding->Interpret(mBody);
    return evaluation;
  }

  Result Macro::EvaluateTemplate(BindingPtr binding)
  {
    Result newName = mName->EvaluateTemplate(binding);
    if (newName.Error()) return newName;

    Result newParameters = mParameters->EvaluateTemplate(binding);
    if (newParameters.Error()) return newParameters;

    Result newBody = mBody->EvaluateTemplate(binding);
    if (newBody.Error()) return newBody;

    return ValuePtr(new Macro(false, dynamic_pointer_cast<Symbol>(newName.Value()), dynamic_pointer_cast<SExp>(newParameters.Value()), dynamic_pointer_cast<SExp>(newBody.Value())));
  }
}
