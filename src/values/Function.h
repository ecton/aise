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
		virtual int Compare(ValuePtr to);
        virtual Result Invoke(BindingPtr binding, SExpPtr arguments) = 0;
	protected:
		Function(bool isTemplate) : Aise::Value(isTemplate) {}
    };
}