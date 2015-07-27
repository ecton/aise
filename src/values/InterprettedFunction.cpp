//
//  InterprettedFunction.cpp
//  aise
//
//  Created by Jonathan Johnson on 6/5/15.
//
//

#include "InterprettedFunction.h"
#include "Environment.h"
#include "Binding.h"

using namespace std;

namespace Aise 
{
  Result InterprettedFunction::Invoke(BindingPtr binding, SExpPtr arguments)
  {
    BindingPtr methodBinding = binding->Environment()->EnterBinding();

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
    binding->Environment()->ExitBinding();
    return evaluation;
  }

  Result InterprettedFunction::EvaluateTemplate(BindingPtr binding)
  {
    Result newName = mName->EvaluateTemplate(binding);
    if (newName.Error()) return newName;

    Result newParameters = mParameters->EvaluateTemplate(binding);
    if (newParameters.Error()) return newParameters;

    Result newBody = mBody->EvaluateTemplate(binding);
    if (newBody.Error()) return newBody;

    return ValuePtr(new InterprettedFunction(false, dynamic_pointer_cast<Symbol>(newName.Value()), dynamic_pointer_cast<SExp>(newParameters.Value()), dynamic_pointer_cast<SExp>(newBody.Value())));
  }
}
