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
		string output = "(";
		if (mLeft) {
			output += mLeft->Description();
		}
		else {
			output += "NULL";
		}
		if (mRight) {
			output += " " + mRight->Description();
		}
		else {
			output += " NULL";
		}
		output += ")";
		return output;
    }
}