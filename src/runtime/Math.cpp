#include "Math.h"
#include "NativeMethod.h"
#include "Integer.h"
#include "Real.h"
#include <math.h>
#include "Boolean.h"

using namespace std;

namespace Aise
{
	class AssociativeMathMethod : public NativeMethod::VariableArgumentMethodImplementation
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

		MathResult GetValue(BindingPtr binding, ValuePtr value)
		{
            Result result = binding->Interpret(value);
            if (result.Error()) return result;
            
			if (auto integer = dynamic_pointer_cast<Integer>(result.Value())) {
				return MathResult(integer->Value());
			}
			else if (auto real = dynamic_pointer_cast<Real>(result.Value())) {
				return MathResult(real->Value());
			}
			else {
				return MathResult(Result("Unknown argument to math function", value));
			}
		}

		virtual Result Invoke(BindingPtr binding, vector<ValuePtr> &arguments) {
            MathResult result = GetValue(binding, arguments[0]);
            for (size_t i = 1; i < arguments.size(); i++) {
                MathResult evaluated = GetValue(binding, arguments[i]);
                if (evaluated.isReal) {
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
            }
            
			if (result.isReal) {
				return Result(ValuePtr(new Real(result.realValue)));
			}
			else {
				return Result(ValuePtr(new Integer(result.intValue)));
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
    
    class NanMethod : public NativeMethod::UnaryMethodImplementation
    {
    public:
        NanMethod() { }
        
        virtual Result Invoke(BindingPtr binding, ValuePtr value)
        {
            auto real = dynamic_pointer_cast<Real>(value);
            if (real) {
                return ValuePtr(new Boolean(isnan(real->Value())));
            }
            
            return ValuePtr(new Boolean(false));
        }
    };
    
    class InfinityMethod : public NativeMethod::UnaryMethodImplementation
    {
    public:
        InfinityMethod() { }
        
        virtual Result Invoke(BindingPtr binding, ValuePtr value)
        {
            auto real = dynamic_pointer_cast<Real>(value);
            if (real) {
                return ValuePtr(new Boolean(isinf(real->Value())));
            }
            
            return ValuePtr(new Boolean(false));
        }
    };

	void Math::Initialize(BindingPtr binding)
	{
		NativeMethod::Initialize(binding, "add", new PlusMethod());
        NativeMethod::Initialize(binding, "subtract", new SubtractMethod());
        NativeMethod::Initialize(binding, "divide", new DivideMethod());
        NativeMethod::Initialize(binding, "multiply", new MultiplyMethod());
        NativeMethod::Initialize(binding, "power", new PowerMethod());
        NativeMethod::Initialize(binding, "nan?", new NanMethod());
        NativeMethod::Initialize(binding, "infinity?", new InfinityMethod());
	}
}