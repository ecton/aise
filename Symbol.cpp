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
}