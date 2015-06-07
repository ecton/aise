#include "Function.h"

namespace Aise
{

	int Function::Compare(std::shared_ptr<Value> to)
	{
		// Functions can't be compared.
		return -1;
	}
    
}