#pragma once
#include "AiseCommon.h"
#include "Value.h"

namespace Aise {
	class SExp : public Value, public std::enable_shared_from_this<SExp>
	{
	public:
		SExp(bool isTemplate, ValuePtr left, ValuePtr right);
		virtual ~SExp();
        
		virtual std::string Description();
		virtual int Compare(ValuePtr to);

		ValuePtr Left() { return mLeft; }
		ValuePtr Right() { return mRight; }
		bool IsEmpty() { return mLeft == NULL && mRight == NULL; }
        
        void ReplaceRight(ValuePtr newRight) { mRight = newRight; }

		virtual Result EvaluateTemplate(BindingPtr binding);
	private:
		ValuePtr mLeft, mRight;
	};
}