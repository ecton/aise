#include "String.h"
#include "Result.h"

using namespace std;

namespace Aise {
  string String::Description() 
  {
    return string("\"") + mValue + "\""; // TODO: Escape the same way we're parsing it
  }

  int String::Compare(ValuePtr to)
  {
    auto otherString = dynamic_pointer_cast<String>(to);
    if (!otherString) return -1;

    return mValue.compare(otherString->mValue);
  }

  Result String::EvaluateTemplate(BindingPtr binding)
  {
    return ValuePtr(new String(false, mValue));
  }
}
