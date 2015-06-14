#include "Collections.h"
#include "Environment.h"
#include "NativeFunction.h"
#include "List.h"
#include "Integer.h"

using namespace std;

namespace Aise
{
	class GetFunction : public NativeFunction::VariableArgumentFunctionImplementation
	{
	public:
		virtual Result Invoke(BindingPtr binding, vector<ValuePtr> &arguments)
		{
			if (arguments.size() != 2) return Result("get takes two parameters", arguments[0]);

			auto collection = binding->Interpret(arguments[0], true);
			if (collection.Error()) return collection;

			auto list = dynamic_pointer_cast<List>(collection.Value());
			if (!list) return Result("Only lists are supported with get currently.", collection.Value());
			auto indexResult = binding->Interpret(arguments[1], true);
			if (indexResult.Error()) return indexResult;

			auto index = dynamic_pointer_cast<Integer>(indexResult.Value());
			if (!index) return Result("get with a list only accepts integer indicies", indexResult.Value());

			return list->Get(index->Value());
		}
	};

	class PushFunction : public NativeFunction::VariableArgumentFunctionImplementation
	{
	public:
		virtual Result Invoke(BindingPtr binding, vector<ValuePtr> &arguments)
		{
			if (arguments.size() < 2) return Result("push takes at least two arguments", arguments[0]);

			auto collection = binding->Interpret(arguments[0], true);
			if (collection.Error()) return collection;

			auto list = dynamic_pointer_cast<List>(collection.Value());
			if (!list) return Result("Only lists are supported with push currently.", collection.Value());

			Result lastResult = Result(ValuePtr(NULL));
			for (size_t i = 1; i < arguments.size(); i++) {
				lastResult = binding->Interpret(arguments[i], true);
				if (lastResult.Error()) return lastResult;
				list->Push(lastResult.Value());
			}

			return lastResult;
		}
	};

	class PopFunction : public NativeFunction::UnaryFunctionImplementation
	{
	public:
		virtual Result Invoke(BindingPtr binding, ValuePtr value)
		{
			auto list = dynamic_pointer_cast<List>(value);
			if (!list) return Result("pop only works on lists.", value);

			return list->Pop();
		}
	};

	void Collections::Initialize(BindingPtr binding)
	{
		NativeFunction::Initialize(binding, "get", new GetFunction());
		NativeFunction::Initialize(binding, "push", new PushFunction());
		NativeFunction::Initialize(binding, "pop", new PopFunction());
	}
}