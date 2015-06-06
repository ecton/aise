#include "Methods.h"
#include "NativeMethod.h"

using namespace std;

namespace Aise
{
    class DefineMethod : public NativeMethod::Implementation
    {
        virtual Result Invoke(BindingPtr binding, SExpPtr sexp)
        {
            /*for (size_t i = 0; i < arguments.size(); i++) {
                Result argument = binding->Interpret(arguments[i]);
                if (argument.Error()) return argument;
                
                auto boolean = dynamic_pointer_cast<Boolean>(argument.Value());
                if (!boolean) return Result("and only takes booleans", arguments[i]);
                if (!boolean->Value()) return binding->Environment()->FalseValue();
            }
            return binding->Environment()->TrueValue();*/
            return Result("Unimplemented", NULL);
        }
    };
    
    void Methods::Initialize(BindingPtr binding)
    {
        NativeMethod::Initialize(binding, "function", new DefineMethod());
    }
}