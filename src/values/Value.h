#pragma once
#include <string>
#include <memory>

namespace Aise {
	class Value
	{
	public:
		~Value();
        virtual std::string Description() = 0;
		static std::shared_ptr<Value> Simplify(std::shared_ptr<Value> value);
	protected:
		Value();
    };
    typedef std::shared_ptr<Value> ValuePtr;
};