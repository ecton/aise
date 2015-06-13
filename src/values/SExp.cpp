#include "SExp.h"
#include "Binding.h"

using namespace std;

namespace Aise {
	SExp::SExp(bool isTemplate, ValuePtr left, ValuePtr right) : Aise::Value(isTemplate)
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

	int SExp::Compare(std::shared_ptr<Value> to)
	{
		auto otherCasted = dynamic_pointer_cast<SExp>(to);
		if (!otherCasted) return -1;

		// Todo
		return -1;
	}

	Result SExp::EvaluateTemplate(BindingPtr binding)
	{
		if (mTemplate) {
			// Templates need to just be returned
			Result newLeft = mLeft->EvaluateTemplate(binding);
			if (newLeft.Error()) return newLeft;

			Result newRight = mRight->EvaluateTemplate(binding);
			if (newRight.Error()) return newRight;

			return ValuePtr(new SExp(false, newLeft.Value(), newRight.Value()));
		}
		else {
			return binding->Interpret(dynamic_pointer_cast<Value>(shared_from_this()), false);
		}
	}
}