#include <memory>
#include <string>

#include "Environment.h"
#include "Value.h"
#include "SExp.h"

namespace Aise {
	typedef std::shared_ptr<Value> ValuePtr;
	typedef std::shared_ptr<std::string> StringPtr;
}