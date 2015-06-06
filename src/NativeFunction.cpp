//
//  NativeFunction.cpp
//  aise
//
//  Created by Jonathan Johnson on 5/31/15.
//
//

#include "NativeFunction.h"
#include "Environment.h"

using namespace std;

namespace Aise {
    std::string NativeFunction::Description() {
        return mName + "<native>";
    }

	Result NativeFunction::Invoke(BindingPtr binding, SExpPtr sexp)
	{
		BindingPtr innerBinding = binding->Environment()->EnterBinding();
		Result result = mImplementation->Invoke(binding, sexp);
		binding->Environment()->ExitBinding();
		return result;
	}
    
    Result NativeFunction::UnaryFunctionImplementation::Invoke(BindingPtr binding, SExpPtr sexp)
    {
        Result result = binding->Interpret(sexp->Right());
        if (result.Error()) return result;
        
        // We either have a already simplified sexpression returned as a value
        // Or we have a sexpression with a right that's null.
        auto rsexp = dynamic_pointer_cast<SExp>(result.Value());
        ValuePtr argument = result.Value();
        if (rsexp) {
            if (rsexp->Right()) return Result("Function only takes one argument", sexp->Right());
            argument = rsexp->Left();
        }
        
        return Invoke(binding, argument);
    }
    
    Result NativeFunction::VariableArgumentFunctionImplementation::Invoke(BindingPtr binding, SExpPtr sexp)
    {
        auto current = dynamic_pointer_cast<SExp>(sexp->Right());
        vector<ValuePtr> arguments;
        while (current) {
            arguments.push_back(current->Left());
            
            auto next = dynamic_pointer_cast<SExp>(current->Right());
            if (!next && current->Right()) return Result("Unexpected value in argument list", current->Right());
            current = next;
        }
        return Invoke(binding, arguments);
    }
}