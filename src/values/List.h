#pragma once
#include "Aise.h"
#include "Value.h"
#include <vector>

namespace Aise {
	class List : public Value
	{
	public:
		List();
		List(std::vector<ValuePtr> vector);
		virtual std::string Description();
		virtual int Compare(std::shared_ptr<Value> to);
		virtual ~List();
	private:
		std::vector<ValuePtr> mVector;
	};
}