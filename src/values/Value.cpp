#include "Value.h"
#include "SExp.h"
#include "Binding.h"

using namespace std;

namespace Aise {

	// This function will take an SExpression that is wrapped in as many nulls as possible, and return the minimum s expression.
	// If it's not an s expression, it will return the original value.
	// For example: ((5 null) null) will return 5, but (5 3) will return (5 3)
	ValuePtr Value::Simplify(BindingPtr binding, ValuePtr value)
	{
		auto sexp = dynamic_pointer_cast<SExp>(value);
		if (sexp) {
			if (sexp->Left() && !sexp->Right()) {
				value = Simplify(binding, sexp->Left());
			}
		}

		while (true) {
			auto result = binding->Interpret(value);
			if (result.Error()) return value;

			// Check to see if we got the same result back
			// If so, 
			if (value == result.Value()) return value;

			value = result.Value();
		}
	}
}