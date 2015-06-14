#pragma once
#include "AiseCommon.h"
#include "Value.h"
#include <vector>

namespace Aise {
	class List : public Value
	{
	public:
		List(bool isTemplate);
		List(bool isTemplate, std::vector<ValuePtr> vector);
		virtual std::string Description();
		virtual int Compare(ValuePtr to);
		virtual ~List();

		virtual Result EvaluateTemplate(BindingPtr binding);

		void Push(ValuePtr value) { mVector.push_back(value); }
		size_t Count() { return mVector.size(); }

	private:
		std::vector<ValuePtr> mVector;
	};
}