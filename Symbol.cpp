//
//  Symbol.cpp
//  aise
//
//  Created by Jonathan Johnson on 5/31/15.
//
//

#include "Symbol.h"
namespace Aise {
    Symbol::Symbol(Aise::Token token) : mToken(token) { }
    
    Symbol::~Symbol() { }
    
    
    std::string Symbol::Description() {
        return mToken.String();
    }
}