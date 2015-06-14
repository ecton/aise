#include "List.h"
#include "Binding.h"

using namespace std;

namespace Aise {
	List::List(bool isTemplate) : Aise::Value(isTemplate)
	{
	}

	List::List(bool isTemplate, vector<ValuePtr> vector) : Aise::Value(isTemplate)
	{
		mVector = vector;
	}

	List::~List()
	{
	}
    
    string List::Description()
    {
        return "";
	}

	int List::Compare(ValuePtr to)
	{
		auto otherCasted = dynamic_pointer_cast<List>(to);
		if (!otherCasted) return -1;

		// Todo
		return -1;
	}

	Result List::EvaluateTemplate(BindingPtr binding)
	{
		throw "Unimplemnted";
		//return ValuePtr(new Integer(false, mValue));
	}
}