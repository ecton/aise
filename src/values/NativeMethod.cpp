//
//  NativeMethod.cpp
//  aise
//
//  Created by Jonathan Johnson on 5/31/15.
//
//

#include "NativeMethod.h"
#include "Environment.h"

using namespace std;

namespace Aise {
    std::string NativeMethod::Description() {
        return mName + "<native>";
    }

	ValuePtr NativeMethod::Invoke(BindingPtr binding, SExpPtr sexp) 
	{
		BindingPtr innerBinding = binding->Environment()->EnterBinding();
		ValuePtr result = mImplementation->Invoke(binding, sexp);
		binding->Environment()->ExitBinding();
		return result;
	}
}