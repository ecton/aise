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

	ValuePtr Value::Simplify(ValuePtr value)
	{
		auto sexp = dynamic_pointer_cast<SExp>(value);
		if (sexp) {
			if (sexp->Left() && !sexp->Right()) {
				value = sexp->Left();
			}
		}
		return value;
	}
}