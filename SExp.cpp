#include "SExp.h"

using namespace std;

namespace Aise {
	SExp::SExp(ValuePtr left, ValuePtr right)
	{
		mLeft = left;
		mRight = right;
	}


	SExp::~SExp()
	{
	}
    
    std::string SExp::Description() {
        string left = mLeft->Description();
        string right = (mRight == NULL ? "<NUL>" : mRight->Description());
        return string("(") + left + " " + right + ")";
    }
}