#pragma once

#include "AiseCommon.h"
#include "Value.h"
#include "Token.h"

namespace Aise {
	class Result
	{
	public:
        Result(std::string message, ValuePtr where);
		Result(ValuePtr value);
		~Result();
        
        bool Error() { return mError; }
        const std::string &ErrorMessage() { return mMessage; }
        ValuePtr Value() { return mValue; }

	protected:
		bool mError;
		std::string mMessage;
		ValuePtr mValue;
	};
}