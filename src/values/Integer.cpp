//
//  Integer.cpp
//  aise
//
//  Created by Jonathan Johnson on 5/31/15.
//
//

#include "Integer.h"
#include <sstream>
#include "Binding.h"

using namespace std;

namespace Aise {
    std::string Integer::Description()
    {
        stringstream ss;
        ss << mValue;
        return ss.str();
	}

	int Integer::Compare(std::shared_ptr<Aise::Value> to)
	{
		auto otherCasted = dynamic_pointer_cast<Integer>(to);
		if (!otherCasted) return -1;

		return (int)(mValue - otherCasted->Value());
	}

	Result Integer::EvaluateTemplate(BindingPtr binding)
	{
		return ValuePtr(new Integer(false, mValue));
	}
}