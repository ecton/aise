#pragma once
#include "AiseCommon.h"
#include "Value.h"
#include <vector>

namespace Aise {
	class List : public Value, public std::enable_shared_from_this<List>
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
		Result Get(size_t index);
		Result Pop();
    Result Remove(size_t index);
    Result Insert(size_t index, ValuePtr value);

    // Overrides
    virtual Result Get(BindingPtr binding, std::vector<ValuePtr> &arguments);
    virtual Result Push(BindingPtr binding, std::vector<ValuePtr> &arguments);
    virtual Result Pop(BindingPtr binding, std::vector<ValuePtr> &arguments);
    virtual Result Count(BindingPtr binding);
    virtual Result Remove(BindingPtr binding, std::vector<ValuePtr> &arguments);
    virtual Result Insert(BindingPtr binding, std::vector<ValuePtr> &arguments);
	private:
		std::vector<ValuePtr> mVector;
	};
}
