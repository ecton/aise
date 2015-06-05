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

		virtual ValuePtr Invoke(BindingPtr binding, SExpPtr sexp) {
			bool isReal = false;
			bool isFirst = true;
			long intValue = 0;
			double realValue = 0;
			SExpPtr current = dynamic_pointer_cast<SExp>(sexp->Right());
			if (!current) throw "Unknown exp to plus";

			while (current) {
				if (auto integer = dynamic_pointer_cast<Integer>(current->Left())) {
					if (isFirst) {
						intValue = integer->Value();
					} else if (isReal) {
						realValue = Operate(realValue, (double)integer->Value());
					}
					else {
						intValue = Operate(intValue, integer->Value());
					}
				}
				else if (auto real = dynamic_pointer_cast<Real>(current->Left())) {
					if (isFirst) {
						realValue = real->Value();
						isReal = true;
					}
					else {
						if (!isReal) {
							isReal = true;
							realValue = intValue;
						}
						realValue = Operate(realValue, real->Value());
					}
				}
				else {
					throw "Unknown lhs to plus";
				}
				current = dynamic_pointer_cast<SExp>(current->Right());
				isFirst = false;
			}
			if (isReal) {
				return ValuePtr(new Real(realValue));
			}
			else {
				return ValuePtr(new Integer(intValue));
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