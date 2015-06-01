#pragma once
#include <string>

namespace Aise {
	class Value
	{
	public:
		~Value();
        virtual std::string Description() = 0;
	protected:
		Value();
    };
    typedef std::shared_ptr<Value> ValuePtr;
};