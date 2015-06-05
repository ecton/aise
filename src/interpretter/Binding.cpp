//
//  Binding.cpp
//  aise
//
//  Created by Jonathan Johnson on 5/31/15.
//
//

#include "Binding.h"

namespace Aise {
    void Binding::Assign(std::string name, ValuePtr value) {
        mTable[name] = value;
    }
    
    ValuePtr Binding::Get(std::string name) {
        return mTable[name];
    }
}