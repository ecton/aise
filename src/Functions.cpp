#include "Functions.h"
#include "NativeFunction.h"

using namespace std;

namespace Aise
{
    class DefineFunction : public NativeFunction::Implementation
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
    
    void Functions::Initialize(BindingPtr binding)
    {
        NativeFunction::Initialize(binding, "function", new DefineFunction());
    }
}