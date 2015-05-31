#include <memory>
#include <string>
#include <vector>

#include "Value.h"

namespace Aise {
	typedef std::shared_ptr<Value> ValuePtr;
    typedef std::shared_ptr<std::string> StringPtr;
}