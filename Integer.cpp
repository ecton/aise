//
//  Integer.cpp
//  aise
//
//  Created by Jonathan Johnson on 5/31/15.
//
//

#include "Integer.h"
#include <sstream>

using namespace std;

namespace Aise {
    std::string Integer::Description()
    {
        stringstream ss;
        ss << mValue;
        return ss.str();
    }
}