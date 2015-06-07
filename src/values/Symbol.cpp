//
//  Symbol.cpp
//  aise
//
//  Created by Jonathan Johnson on 5/31/15.
//
//

#include "Symbol.h"

using namespace std;

namespace Aise {
    Symbol::Symbol(shared_ptr<Aise::Token> token) : mToken(token) { }
    
    Symbol::~Symbol() { }
    
    
    std::string Symbol::Description() {
        return mToken->String();
	}

	int Symbol::Compare(std::shared_ptr<Value> to)
	{
		auto otherCasted = dynamic_pointer_cast<Symbol>(to);
		if (!otherCasted) return -1;

		return String().compare(otherCasted->String());
	}
}