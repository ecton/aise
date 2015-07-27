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

			return collection.Value()->Get(binding, arguments);
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

      return collection.Value()->Push(binding, arguments);
		}
	};

	class PopFunction : public NativeFunction::VariableArgumentFunctionImplementation
	{
	public:
		virtual Result Invoke(BindingPtr binding, vector<ValuePtr> &arguments)
		{
			auto collection = binding->Interpret(arguments[0], true);
      if (collection.Error()) return collection;

			return collection.Value()->Pop(binding, arguments);
		}
	};

	class CountFunction : public NativeFunction::UnaryFunctionImplementation
	{
	public:
		virtual Result Invoke(BindingPtr binding, ValuePtr value)
		{
      return value->Count(binding);
		}
	};

  class RemoveFunction : public NativeFunction::VariableArgumentFunctionImplementation
	{
	public:
		virtual Result Invoke(BindingPtr binding, vector<ValuePtr> &arguments)
		{
			if (arguments.size() != 2) return Result("remove takes two arguments", arguments[0]);

			auto collection = binding->Interpret(arguments[0], true);
			if (collection.Error()) return collection;

      return collection.Value()->Remove(binding, arguments);
		}
	};

  class InsertFunction : public NativeFunction::VariableArgumentFunctionImplementation
	{
	public:
		virtual Result Invoke(BindingPtr binding, vector<ValuePtr> &arguments)
		{
			if (arguments.size() < 3) return Result("insert takes at least three arguments", arguments[0]);

			auto collection = binding->Interpret(arguments[0], true);
			if (collection.Error()) return collection;

      return collection.Value()->Insert(binding, arguments);
		}
	};



	void Collections::Initialize(BindingPtr binding)
	{
		NativeFunction::Initialize(binding, "get", new GetFunction());
		NativeFunction::Initialize(binding, "push", new PushFunction());
		NativeFunction::Initialize(binding, "pop", new PopFunction());
		NativeFunction::Initialize(binding, "count", new CountFunction());
    NativeFunction::Initialize(binding, "remove", new RemoveFunction());
    NativeFunction::Initialize(binding, "insert", new InsertFunction());
	}
}
