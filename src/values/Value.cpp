#include "Value.h"
#include "SExp.h"

using namespace std;

namespace Aise {
	Value::Value()
	{
	}

	Value::~Value()
	{
	}

	// This function will take an SExpression that is wrapped in as many nulls as possible, and return the minimum s expression.
	// If it's not an s expression, it will return the original value.
	// For example: ((5 null) null) will return 5, but (5 3) will return (5 3)
	ValuePtr Value::Simplify(ValuePtr value)
	{
		auto sexp = dynamic_pointer_cast<SExp>(value);
		if (sexp) {
			if (sexp->Left() && !sexp->Right()) {
				value = Simplify(sexp->Left());
			}
		}
		return value;
	}
}