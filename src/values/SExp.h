#pragma once
#include "AiseCommon.h"
#include "Value.h"

namespace Aise {
	class SExp : private std::enable_shared_from_this<SExp>, public Value
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
        
        static ValuePtr Create(bool isTemplate, ValuePtr left, ValuePtr right) { return ValuePtr(dynamic_cast<Value *>(new SExp(isTemplate, left, right))); }
	private:
		ValuePtr mLeft, mRight;
	};
}