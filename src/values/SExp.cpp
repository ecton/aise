#include "SExp.h"
#include "Binding.h"

using namespace std;

namespace Aise {
  SExp::SExp(bool isTemplate, ValuePtr left, ValuePtr right) : Aise::Value(isTemplate)
  {
    mLeft = left;
    mRight = right;
  }


  SExp::~SExp()
  {
  }

  std::string SExp::Description() {
    string output = "(";
    if (mLeft) {
      output += mLeft->Description();
    }
    else {
      output += "NULL";
    }
    if (mRight) {
      output += " " + mRight->Description();
    }
    else {
      output += " NULL";
    }
    output += ")";
    return output;
  }

  int SExp::Compare(ValuePtr to)
  {
    auto otherCasted = dynamic_pointer_cast<SExp>(to);
    if (!otherCasted) return -1;

    // TODO
    return -1;
  }

  Result SExp::EvaluateTemplate(BindingPtr binding)
  {
    if (mTemplate) {
      // Templates need to just be returned
      Result newLeft = ValuePtr(NULL);
      if (mLeft) {
        newLeft = mLeft->EvaluateTemplate(binding);
        if (newLeft.Error()) return newLeft;
      }

      Result newRight = ValuePtr(NULL);
      if (mRight) {
        newRight = mRight->EvaluateTemplate(binding);
        if (newRight.Error()) return newRight;
      }

      return SExp::Create(false, newLeft.Value(), newRight.Value());
    }
    else {
      return binding->Interpret(dynamic_pointer_cast<Value>(shared_from_this()), false);
    }
  }
}