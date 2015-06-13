#pragma once
#include <string>
#include <memory>

namespace Aise {
	class Binding; 
	class Result;
	class Value
	{
	public:
		virtual ~Value() { }
        virtual std::string Description() = 0;
		static std::shared_ptr<Value> Simplify(std::shared_ptr<Value> value);
		virtual int Compare(std::shared_ptr<Value> to) = 0;
		bool IsTemplate();
		virtual Result EvaluateTemplate(std::shared_ptr<Aise::Binding> binding) = 0;
	protected:
		Value(bool isTemplate) : mTemplate(mTemplate) { }
		bool mTemplate;
    };
    typedef std::shared_ptr<Value> ValuePtr;
};