#include "Flow.h"
#include "Environment.h"
#include "NativeFunction.h"

using namespace std;

namespace Aise
{
	class DoFunction : public NativeFunction::Implementation
	{
		virtual Result Invoke(BindingPtr binding, SExpPtr sexp)
		{
			// sexp left is "do", right is the container of the first statement
			Result lastResult = dynamic_pointer_cast<Value>(sexp);
			while (sexp) {
				lastResult = binding->Interpret(sexp->Left());
				if (lastResult.Error()) break;

				auto next = sexp->Right();
				sexp = dynamic_pointer_cast<SExp>(next);
				if (next && !sexp) return Result("Only SExpressions can be passed to do", next);
			}
			if (lastResult.Error()) return lastResult;

			// If not an error, we'll have the result in an sexpression like (result <null>).
			// Let's return the simple value
			return Value::Simplify(lastResult.Value());
		}
	};

	void Flow::Initialize(BindingPtr binding)
	{
		NativeFunction::Initialize(binding, "do", new DoFunction());
	}
}