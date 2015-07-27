//
//  Real.cpp
//  aise
//
//  Created by Jonathan Johnson on 5/31/15.
//
//

#include "Real.h"

#include <sstream>
#include "Binding.h"

using namespace std;

namespace Aise {
    string Real::Description()
    {
        stringstream ss;
        ss << mValue;
        return ss.str();
  }

  int Real::Compare(std::shared_ptr<Aise::Value> to)
  {
    auto otherCasted = dynamic_pointer_cast<Real>(to);
    if (!otherCasted) return -1;

    if (mValue == otherCasted->Value()) return 0;
    if (mValue > otherCasted->Value()) return 1;
    return -1;
  }

  Result Real::EvaluateTemplate(BindingPtr binding)
  {
    return ValuePtr(new Real(false, mValue));
  }
}