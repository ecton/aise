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
}