#include "Flow.h"
#include "Environment.h"
#include "NativeFunction.h"
#include "Boolean.h"

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
				lastResult = binding->Interpret(sexp->Left(), true);
				if (lastResult.Error()) break;

				auto next = sexp->Right();
				sexp = dynamic_pointer_cast<SExp>(next);
				if (next && !sexp) return Result("Only SExpressions can be passed to do", next);
			}
			return lastResult;
		}
	};

	class IfFunction : public NativeFunction::Implementation
	{
		virtual Result Invoke(BindingPtr binding, SExpPtr sexp)
		{
			// sexp left is "if", right is the container of the test condition
			auto conditionContainer = dynamic_pointer_cast<SExp>(sexp->Right());
			if (!conditionContainer) return Result("Expected sexp for if condition", sexp);
			auto condition = binding->Interpret(conditionContainer->Left());
			if (condition.Error()) return condition;

			// Condition needs to be a boolean
			auto conditionBoolean = dynamic_pointer_cast<Boolean>(Value::Simplify(condition.Value()));
			if (!conditionBoolean) return Result("if requires a boolean condition", condition.Value());

			auto resultContainer = dynamic_pointer_cast<SExp>(conditionContainer->Right());
			if (!resultContainer) return Result("if requires a sexp after the condition", conditionContainer);

			// If true, then return the result of interpretting the sexp
			if (conditionBoolean->Value()) {
				return binding->Interpret(resultContainer->Left(), true);
			}

			// Check for else
			if (resultContainer->Right()) {
				auto elseContainer = dynamic_pointer_cast<SExp>(resultContainer->Right());
				if (!elseContainer) return Result("Invalid expression after if -- expected else", resultContainer->Right());
				auto elseSymbol = dynamic_pointer_cast<Symbol>(elseContainer->Left());
				if (!elseSymbol || elseSymbol->String() != "else") return Result("Missing else", elseContainer->Left());
				return binding->Interpret(elseContainer->Right(), true);
			}

			// Lastly, if there was no else and this evaluated to false, we want to return false.
			return binding->Environment()->FalseValue();
		}
	};



	void Flow::Initialize(BindingPtr binding)
	{
		NativeFunction::Initialize(binding, "do", new DoFunction());
		NativeFunction::Initialize(binding, "if", new IfFunction());
	}
}