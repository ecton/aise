#pragma once

#include "Aise.h"
#import "Value.h"

namespace Aise {
	class Result
	{
	public:
		Result(std::string message);
		Result(ValuePtr value);
		~Result();

	protected:
		bool mError;
		std::string mMessage;
		ValuePtr mValue;
	};
}