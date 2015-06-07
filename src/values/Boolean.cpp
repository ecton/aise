//
//  Integer.cpp
//  aise
//
//  Created by Jonathan Johnson on 5/31/15.
//
//

#include "Boolean.h"
#include <sstream>

using namespace std;

namespace Aise {
    Boolean::Boolean(shared_ptr<Aise::Token> token) : mToken(token)
    {
         stringstream(token->String()) >> boolalpha >> mValue;
    }
    
    std::string Boolean::Description()
    {
        stringstream ss;
        ss << boolalpha << mValue;
        return ss.str();
    }

	int Boolean::Compare(std::shared_ptr<Aise::Value> to)
	{
		auto otherCasted = dynamic_pointer_cast<Boolean>(to);
		if (!otherCasted) return -1;

		if (mValue == otherCasted->Value()) return 0;
		if (mValue) return 1;
		return -1;
	}
}