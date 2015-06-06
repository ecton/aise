#pragma once
#include "Value.h"
#include "Result.h"
#include "SExp.h"
#include "Binding.h"

namespace Aise
{
    class Function : public Value
    {
    public:
        virtual Result Invoke(BindingPtr binding, SExpPtr arguments) = 0;
    };
}