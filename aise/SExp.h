#pragma once
#include "Aise.h"

namespace Aise {
	class SExp : Value
	{
	public:
		SExp(ValuePtr left, ValuePtr right);
		virtual ~SExp();

		ValuePtr Left() { return mLeft; }
		ValuePtr Right() { return mRight; }
	private:
		ValuePtr mLeft, mRight;
	};
}