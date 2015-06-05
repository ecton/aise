#include "Math.h"
#include "NativeMethod.h"
#include "Integer.h"
#include "Real.h"

using namespace std;

namespace Aise
{
	class AssociativeMathMethod : public NativeMethod::Implementation
	{
	public:
		AssociativeMathMethod() { }
		virtual double Operate(double left, double right) = 0;
		virtual long Operate(long left, long right) = 0;

		typedef struct {
			bool isReal;
			long intValue;
			double realValue;
		} MathResult;

		MathResult GetValue(BindingPtr binding, ValuePtr value, bool firstPass = true)
		{
			if (auto integer = dynamic_pointer_cast<Integer>(value)) {
				return MathResult{ false, integer->Value() };
			}
			else if (auto real = dynamic_pointer_cast<Real>(value)) {
				return MathResult{ true, 0, real->Value() };
			}
			else {
				if (!firstPass) throw "Unknown argument to math function";

				return GetValue(binding, binding->Environment()->Interpret(binding, value), false);
			}
		}

		virtual ValuePtr Invoke(BindingPtr binding, SExpPtr sexp) {
			MathResult result = { 0 };
			bool isFirst = true;
			SExpPtr current = dynamic_pointer_cast<SExp>(sexp->Right());
			if (!current) throw "Unknown exp to plus";

			while (current) {
				MathResult evaluated = GetValue(binding, current->Left());
				if (isFirst) {
					result = evaluated;
					isFirst = false;
				}
				else if (evaluated.isReal) {
					if (!result.isReal) {
						result.isReal = true;
						result.realValue = result.intValue;
					}
					result.realValue = Operate(result.realValue, evaluated.realValue);
				}
				else {
					result.intValue = Operate(result.intValue, evaluated.intValue);
				}
				current = dynamic_pointer_cast<SExp>(current->Right());
			}
			if (result.isReal) {
				return ValuePtr(new Real(result.realValue));
			}
			else {
				return ValuePtr(new Integer(result.intValue));
			}
		}
	};

	class PlusMethod : public AssociativeMathMethod
	{
	public:
		virtual double Operate(double left, double right) { return left + right; }
		virtual long Operate(long left, long right)  { return left + right; }
	};

	class SubtractMethod : public AssociativeMathMethod
	{
	public:
		virtual double Operate(double left, double right) { return left - right; }
		virtual long Operate(long left, long right)  { return left - right; }
	};

	void Math::Initialize(BindingPtr binding)
	{
		NativeMethod::Initialize(binding, "add", new PlusMethod());
		NativeMethod::Initialize(binding, "subtract", new SubtractMethod());
	}
}