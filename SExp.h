#pragma once
#include "Aise.h"

namespace Aise {
	class SExp : public Value
	{
	public:
		SExp(ValuePtr left, ValuePtr right);
		virtual ~SExp();
        
        virtual std::string Description();

		ValuePtr Left() { return mLeft; }
		ValuePtr Right() { return mRight; }
        
        void ReplaceRight(ValuePtr newRight) { mRight = newRight; }
	private:
		ValuePtr mLeft, mRight;
	};
}