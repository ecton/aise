//
//  Symbol.cpp
//  aise
//
//  Created by Jonathan Johnson on 5/31/15.
//
//

#include "Symbol.h"
#include "Binding.h"

using namespace std;

namespace Aise {
    Symbol::Symbol(bool isTemplate, shared_ptr<Aise::Token> token) : Aise::Value(isTemplate), mToken(token) { }
    
    Symbol::~Symbol() { }
    
    
    std::string Symbol::Description() {
        return mToken->String();
	}

	int Symbol::Compare(ValuePtr to)
	{
		auto otherCasted = dynamic_pointer_cast<Symbol>(to);
		if (!otherCasted) return -1;

		return String().compare(otherCasted->String());
	}

	Result Symbol::EvaluateTemplate(BindingPtr binding)
	{
		if (mTemplate) {
			return ValuePtr(new Symbol(false, mToken));
		}
		else {
			ValuePtr value = binding->Get(mToken->String());
			if (value) return value;
			return Result("Unknown Reference", NULL); // TODO
		}
	}
}