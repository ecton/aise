#include "Logic.h"
#include "NativeMethod.h"
#include "Boolean.h"

using namespace std;

namespace Aise
{
    class AndMethod : public NativeMethod::VariableArgumentMethodImplementation
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
    class OrMethod : public NativeMethod::VariableArgumentMethodImplementation
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
    
    class NotMethod : public NativeMethod::UnaryMethodImplementation
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
        NativeMethod::Initialize(binding, "and", new AndMethod());
        NativeMethod::Initialize(binding, "or", new OrMethod());
        NativeMethod::Initialize(binding, "not", new NotMethod());
    }
}