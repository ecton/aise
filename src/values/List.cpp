#include "List.h"

using namespace std;

namespace Aise {
	List::List()
	{
	}

	List::List(vector<ValuePtr> vector) 
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

	int List::Compare(std::shared_ptr<Value> to)
	{
		auto otherCasted = dynamic_pointer_cast<List>(to);
		if (!otherCasted) return -1;

		// Todo
		return -1;
	}
}