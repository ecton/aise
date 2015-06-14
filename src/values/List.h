#pragma once
#include "Aise.h"
#include "Value.h"
#include <vector>

namespace Aise {
	class List : public Value
	{
	public:
		List(bool isTemplate);
		List(bool isTemplate, std::vector<ValuePtr> vector);
		virtual std::string Description();
		virtual int Compare(std::shared_ptr<Value> to);
		virtual ~List();

		virtual Result EvaluateTemplate(std::shared_ptr<Aise::Binding> binding);
	private:
		std::vector<ValuePtr> mVector;
	};
}