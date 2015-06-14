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
			auto conditionBoolean = dynamic_pointer_cast<Boolean>(Value::Simplify(binding, condition.Value()));
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

	class SetFunction : public NativeFunction::Implementation
	{
		virtual Result Invoke(BindingPtr binding, SExpPtr sexp)
		{
			// sexp left is "set", right is the container of the symbol
			auto nameContainer = dynamic_pointer_cast<SExp>(sexp->Right());
			if (!nameContainer) return Result("Expected sexp for set name and value", sexp);

			// name needs to be a symbol 
			auto name = dynamic_pointer_cast<Symbol>(nameContainer->Left());
			if (!name) {
				// Try to interpret it to see if the result is a symbol
				auto nameResult = binding->Interpret(nameContainer->Left(), true);
				if (nameResult.Error()) return nameResult;
				name = dynamic_pointer_cast<Symbol>(nameResult.Value());
				if (!name) return Result("set requires name to be a symbol", nameResult.Value());
			}

			auto value = binding->Interpret(nameContainer->Right(), true);
			if (value.Error()) return value;

			binding->Assign(name->String(), value.Value());
			return value;
		}
	};

	class WhileFunction : public NativeFunction::Implementation
	{
		virtual Result Invoke(BindingPtr binding, SExpPtr sexp)
		{
			// sexp left is "while", right is the container of the test condition
			auto conditionContainer = dynamic_pointer_cast<SExp>(sexp->Right());
			if (!conditionContainer) return Result("Expected sexp for while condition", sexp);

			Result lastResult = ValuePtr(NULL);
			while (true) {
				// Interpret the condition
				auto condition = binding->Interpret(conditionContainer->Left());
				if (condition.Error()) return condition;

				// Condition needs to be a boolean
				auto conditionBoolean = dynamic_pointer_cast<Boolean>(Value::Simplify(binding, condition.Value()));
				if (!conditionBoolean) return Result("while requires a boolean condition", condition.Value());

				if (!conditionBoolean->Value()) break;

				lastResult = binding->Interpret(conditionContainer->Right(), true);
				if (lastResult.Error()) return lastResult;
			}

			return lastResult;
		}
	};

	class ComparisonFunction : public NativeFunction::Implementation
	{
		virtual Result Invoke(BindingPtr binding, SExpPtr sexp)
		{
			// sexp left is "equals", right is the container of the left and right
			auto valuesContainer = dynamic_pointer_cast<SExp>(sexp->Right());
			if (!valuesContainer) return Result("Expected sexp for equals condition", sexp);

			auto leftResult = binding->Interpret(valuesContainer->Left(), true);
			if (leftResult.Error()) return leftResult;

			auto rightResult = binding->Interpret(valuesContainer->Right(), true);
			if (rightResult.Error()) return rightResult;

			int comparison = leftResult.Value()->Compare(rightResult.Value());

			if (InterpretResult(comparison)) {
				return binding->Environment()->TrueValue();
			}
			else {
				return binding->Environment()->FalseValue();
			}
		}
		virtual bool InterpretResult(int result) = 0;

	};

	class EqualsFunction : public ComparisonFunction
	{
		virtual bool InterpretResult(int result) {
			return result == 0;
		}
	};

	class LessThanFunction : public ComparisonFunction
	{
		virtual bool InterpretResult(int result) {
			return result < 0;
		}
	};

	class LessThanOrEqualFunction : public ComparisonFunction
	{
		virtual bool InterpretResult(int result) {
			return result <= 0;
		}
	};

	class GreaterThanFunction : public ComparisonFunction
	{
		virtual bool InterpretResult(int result) {
			return result > 0;
		}
	};

	class GreaterThanOrEqualFunction : public ComparisonFunction
	{
		virtual bool InterpretResult(int result) {
			return result >= 0;
		}
	};



	void Flow::Initialize(BindingPtr binding)
	{
		NativeFunction::Initialize(binding, "do", new DoFunction());
		NativeFunction::Initialize(binding, "if", new IfFunction());
		NativeFunction::Initialize(binding, "set", new SetFunction());
		NativeFunction::Initialize(binding, "while", new WhileFunction());
		NativeFunction::Initialize(binding, "equals", new EqualsFunction());
		NativeFunction::Initialize(binding, "less-than", new LessThanFunction());
		NativeFunction::Initialize(binding, "less-than-or-equal", new LessThanOrEqualFunction());
		NativeFunction::Initialize(binding, "greater-than", new GreaterThanFunction());
		NativeFunction::Initialize(binding, "greater-than-or-equal", new GreaterThanOrEqualFunction());
	}
}