//
//  NativeMethod.cpp
//  aise
//
//  Created by Jonathan Johnson on 5/31/15.
//
//

#include "NativeMethod.h"

using namespace std;

namespace Aise {
    std::string NativeMethod::Description() {
        return mName + "<native>";
    }
}