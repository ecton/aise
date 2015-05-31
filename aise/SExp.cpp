#include "SExp.h"

namespace Aise {
	SExp::SExp(ValuePtr left, ValuePtr right)
	{
		mLeft = left;
		mRight = right;
	}


	SExp::~SExp()
	{
	}
}