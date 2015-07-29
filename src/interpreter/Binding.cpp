//
//  Binding.cpp
//  aise
//
//  Created by Jonathan Johnson on 5/31/15.
//
//

#include "Binding.h"
#include "Environment.h"

namespace Aise {
  Binding::Binding(Aise::Environment *environment) : mEnvironment(environment) { }
    
  Result Binding::Interpret(ValuePtr expression, bool simplify)
  {
    Result result = mEnvironment->Interpret(shared_from_this(), expression);
    if (simplify && !result.Error()) {
      return Value::Simplify(shared_from_this(), result.Value());
    }
    return result;
  }
  
  void Binding::Assign(std::string name, ValuePtr value) {
    mTable[name] = value;
  }
  
  ValuePtr Binding::Get(std::string name) {
    return mTable[name];
  }
}