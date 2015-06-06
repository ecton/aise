#include "Logic.h"
#include "NativeFunction.h"
#include "Boolean.h"

using namespace std;

namespace Aise
{
    class AndFunction : public NativeFunction::VariableArgumentFunctionImplementation
    {
        virtual Result Invoke(BindingPtr binding, vector<ValuePtr> &arguments) {
            for (size_t i = 0; i < arguments.size(); i++) {
                Result argument = binding->Interpret(arguments[i]);
                if (argument.Error()) return argument;
                
                auto boolean = dynamic_pointer_cast<Boolean>(argument.Value());
                if (!boolean) return Result("and only takes booleans", arguments[i]);
                if (!boolean->Value()) return binding->Environment()->FalseValue();
            }
            return binding->Environment()->TrueValue();
        }
    };
    class OrFunction : public NativeFunction::VariableArgumentFunctionImplementation
    {
        virtual Result Invoke(BindingPtr binding, vector<ValuePtr> &arguments) {
            for (size_t i = 0; i < arguments.size(); i++) {
                Result argument = binding->Interpret(arguments[i]);
                if (argument.Error()) return argument;
                
                auto boolean = dynamic_pointer_cast<Boolean>(argument.Value());
                if (!boolean) return Result("and only takes booleans", arguments[i]);
                if (boolean->Value()) return binding->Environment()->TrueValue();
            }
            return binding->Environment()->FalseValue();
        }
    };
    
    class NotFunction : public NativeFunction::UnaryFunctionImplementation
    {
    public:
        virtual Result Invoke(BindingPtr binding, ValuePtr value)
        {
            auto boolean = dynamic_pointer_cast<Boolean>(value);
            if (boolean) {
                if (boolean->Value()) {
                    return binding->Environment()->FalseValue();
                } else {
                    return binding->Environment()->TrueValue();
                }
            }
            
            return Result("not only takes booleans.", value);
        }
    };
    
    void Logic::Initialize(BindingPtr binding)
    {
        NativeFunction::Initialize(binding, "and", new AndFunction());
        NativeFunction::Initialize(binding, "or", new OrFunction());
        NativeFunction::Initialize(binding, "not", new NotFunction());
    }
}