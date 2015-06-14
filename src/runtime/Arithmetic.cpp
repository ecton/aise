#include "Arithmetic.h"
#include "NativeFunction.h"
#include "Integer.h"
#include "Real.h"
#include <math.h>
#include "Boolean.h"

using namespace std;

namespace Aise
{
	class AssociativeMathFunction : public NativeFunction::VariableArgumentFunctionImplementation
	{
	public:
		AssociativeMathFunction() { }
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
            Result result = binding->Interpret(value, true);
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
			if (arguments.size() == 0) return Result("No arguments provided to math operation", NULL);
            MathResult result = GetValue(binding, arguments[0]);
			if (result.error.Error()) return result.error;

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
				return Result(ValuePtr(new Real(false, result.realValue)));
			}
			else {
				return Result(ValuePtr(new Integer(false, result.intValue)));
			}
		}
	};

	class PlusFunction : public AssociativeMathFunction
	{
	public:
		virtual double Operate(double left, double right) { return left + right; }
		virtual long Operate(long left, long right)  { return left + right; }
	};

	class SubtractFunction : public AssociativeMathFunction
	{
	public:
		virtual double Operate(double left, double right) { return left - right; }
		virtual long Operate(long left, long right)  { return left - right; }
    };
    
    class MultiplyFunction : public AssociativeMathFunction
    {
    public:
        virtual double Operate(double left, double right) { return left * right; }
        virtual long Operate(long left, long right)  { return left * right; }
    };
    
    class DivideFunction : public AssociativeMathFunction
    {
    public:
        virtual double Operate(double left, double right) { return left / right; }
        virtual long Operate(long left, long right)  { return left / right; }
    };
    
    class PowerFunction : public AssociativeMathFunction
    {
    public:
        virtual double Operate(double left, double right) { return pow(left, right); }
        virtual long Operate(long left, long right)  { return (long)pow(left, right); }
    };
    
    class NanFunction : public NativeFunction::UnaryFunctionImplementation
    {
    public:
        NanFunction() { }
        
        virtual Result Invoke(BindingPtr binding, ValuePtr value)
        {
            auto real = dynamic_pointer_cast<Real>(value);
            if (real) {
                return ValuePtr(new Boolean(false, isnan(real->Value())));
            }
            
            return ValuePtr(new Boolean(false, false));
        }
    };
    
    class InfinityFunction : public NativeFunction::UnaryFunctionImplementation
    {
    public:
        InfinityFunction() { }
        
        virtual Result Invoke(BindingPtr binding, ValuePtr value)
        {
            auto real = dynamic_pointer_cast<Real>(value);
            if (real) {
                return ValuePtr(new Boolean(false, isinf(real->Value())));
            }
            
            return ValuePtr(new Boolean(false, false));
        }
    };

	void Arithmetic::Initialize(BindingPtr binding)
	{
		NativeFunction::Initialize(binding, "add", new PlusFunction());
        NativeFunction::Initialize(binding, "subtract", new SubtractFunction());
        NativeFunction::Initialize(binding, "divide", new DivideFunction());
        NativeFunction::Initialize(binding, "multiply", new MultiplyFunction());
        NativeFunction::Initialize(binding, "power", new PowerFunction());
        NativeFunction::Initialize(binding, "nan?", new NanFunction());
        NativeFunction::Initialize(binding, "infinity?", new InfinityFunction());
	}
}