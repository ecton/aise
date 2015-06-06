#include "Value.h"
#include "Result.h"
#include "SExp.h"
#include "Binding.h"

namespace Aise
{
    class Method : public Value
    {
    public:
        virtual Result Invoke(BindingPtr binding, SExpPtr arguments) = 0;
    };
}