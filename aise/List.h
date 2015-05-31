#pragma once
#include "Aise.h"
#include <vector>

namespace Aise {
	class List : Value
	{
	public:
		List();
		List(std::vector<ValuePtr> vector);
		virtual ~List();
	private:
		std::vector<ValuePtr> mVector;
	};
}