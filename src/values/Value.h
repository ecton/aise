#pragma once
#include "AiseCommon.h"

namespace Aise {
	class Binding; 
	class Result;
	class Value
	{
	public:
		virtual ~Value() { }
        virtual std::string Description() = 0;
		static ValuePtr Simplify(BindingPtr binding, ValuePtr value);
		virtual int Compare(ValuePtr to) = 0;
		bool IsTemplate() {
			return mTemplate;
		}
		virtual Result EvaluateTemplate(BindingPtr binding) = 0;
	protected:
		Value(bool isTemplate) : mTemplate(isTemplate) { }
		bool mTemplate;
    };
};