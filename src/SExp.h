#pragma once
#include "Aise.h"
#include "Value.h"

namespace Aise {
	class SExp : public Value
	{
	public:
		SExp(ValuePtr left, ValuePtr right);
		virtual ~SExp();
        
        virtual std::string Description();

		ValuePtr Left() { return mLeft; }
		ValuePtr Right() { return mRight; }
		bool IsEmpty() { return mLeft == NULL && mRight == NULL; }
        
        void ReplaceRight(ValuePtr newRight) { mRight = newRight; }
	private:
		ValuePtr mLeft, mRight;
	};
    typedef std::shared_ptr<SExp> SExpPtr;
}