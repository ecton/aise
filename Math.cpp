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

		class MathResult {
        public:
            MathResult(long value) : intValue(value), isReal(false), error(Result(NULL)) { }
            MathResult(double value) : realValue(value), isReal(true), error(Result(NULL)) { }
            MathResult(Result error) : error(error) { }
			bool isReal;
			long intValue;
			double realValue;
            Result error;
		};

		MathResult GetValue(BindingPtr binding, ValuePtr value, bool firstPass = true)
		{
			if (auto integer = dynamic_pointer_cast<Integer>(value)) {
				return MathResult(integer->Value());
			}
			else if (auto real = dynamic_pointer_cast<Real>(value)) {
				return MathResult(real->Value());
			}
			else {
				if (!firstPass) throw "Unknown argument to math function";
                
                auto result = binding->Environment()->Interpret(binding, value);
                if (result.Error()) return MathResult(result);

                return GetValue(binding, result.Value(), false);
			}
		}

		virtual ValuePtr Invoke(BindingPtr binding, SExpPtr sexp) {
			MathResult result = MathResult(0L);
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
				else if (result.isReal) {
                    result.realValue = Operate(result.realValue, (double)evaluated.intValue);
                } else {
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
    
    class MultiplyMethod : public AssociativeMathMethod
    {
    public:
        virtual double Operate(double left, double right) { return left * right; }
        virtual long Operate(long left, long right)  { return left * right; }
    };
    
    class DivideMethod : public AssociativeMathMethod
    {
    public:
        virtual double Operate(double left, double right) { return left / right; }
        virtual long Operate(long left, long right)  { return left / right; }
    };
    
    class PowerMethod : public AssociativeMathMethod
    {
    public:
        virtual double Operate(double left, double right) { return pow(left, right); }
        virtual long Operate(long left, long right)  { return (long)pow(left, right); }
    };

	void Math::Initialize(BindingPtr binding)
	{
		NativeMethod::Initialize(binding, "add", new PlusMethod());
        NativeMethod::Initialize(binding, "subtract", new SubtractMethod());
        NativeMethod::Initialize(binding, "divide", new DivideMethod());
        NativeMethod::Initialize(binding, "multiply", new MultiplyMethod());
        NativeMethod::Initialize(binding, "power", new PowerMethod());
	}
}