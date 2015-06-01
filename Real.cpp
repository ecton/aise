//
//  Real.cpp
//  aise
//
//  Created by Jonathan Johnson on 5/31/15.
//
//

#include "Real.h"
#include <sstream>

using namespace std;

namespace Aise {
    string Real::Description()
    {
        stringstream ss;
        ss << mValue;
        return ss.str();
    }
}