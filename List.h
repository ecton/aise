#pragma once
#include "Aise.h"
#import "Value.h"
#include <vector>

namespace Aise {
	class List : public Value
	{
	public:
		List();
		List(std::vector<ValuePtr> vector);
        virtual std::string Description();
		virtual ~List();
	private:
		std::vector<ValuePtr> mVector;
	};
}