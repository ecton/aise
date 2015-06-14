#include "Functions.h"
#include "NativeFunction.h"
#include "InterprettedFunction.h"
#include "Macro.h"

using namespace std;

namespace Aise
{
    class DefineFunction : public NativeFunction::Implementation
    {
        virtual Result Invoke(BindingPtr binding, SExpPtr sexp)
        {
			// Syntax is (function name (args ...) (body))
			// Left starts off as "function", right is an SExp of (name sexp)
			auto nameContainer = dynamic_pointer_cast<SExp>(sexp->Right());
			if (!nameContainer) return Result("Expected function name.", sexp->Right());

			auto name = dynamic_pointer_cast<Symbol>(nameContainer->Left());
			if (!name) return Result("Expected function name to be a symbol", nameContainer);

			auto argumentsContainer = dynamic_pointer_cast<SExp>(nameContainer->Right());
			if (!argumentsContainer) return Result("Expected function arguments", nameContainer->Right());

			auto arguments = dynamic_pointer_cast<SExp>(argumentsContainer->Left());
			if (!arguments) return Result("Expected function arguments to be an sexpression", argumentsContainer);

			auto body = dynamic_pointer_cast<SExp>(argumentsContainer->Right());
			if (!body) return Result("Expected function body to be an sexpression", argumentsContainer);

			auto newFunction = ValuePtr(new InterprettedFunction(false, name, arguments, body));
			binding->Assign(name->String(), newFunction);
			return newFunction;
        }
	};

	class EvalFunction : public NativeFunction::UnaryFunctionImplementation
	{
		virtual Result Invoke(BindingPtr binding, ValuePtr value)
		{
			// This is the simplest function of them all, just interpret the value.
			// This is useful for finally invoking a template.
			return binding->Interpret(value, true);
		}
	};

	class DefineMacro : public NativeFunction::Implementation
	{
		virtual Result Invoke(BindingPtr binding, SExpPtr sexp)
		{
			// Syntax is (macro name (args ...) (body))
			// Left starts off as "macro", right is an SExp of (name sexp)
			auto nameContainer = dynamic_pointer_cast<SExp>(sexp->Right());
			if (!nameContainer) return Result("Expected function name.", sexp->Right());

			auto name = dynamic_pointer_cast<Symbol>(nameContainer->Left());
			if (!name) return Result("Expected function name to be a symbol", nameContainer);

			auto argumentsContainer = dynamic_pointer_cast<SExp>(nameContainer->Right());
			if (!argumentsContainer) return Result("Expected function arguments", nameContainer->Right());

			auto arguments = dynamic_pointer_cast<SExp>(argumentsContainer->Left());
			if (!arguments) return Result("Expected function arguments to be an sexpression", argumentsContainer);

			auto body = dynamic_pointer_cast<SExp>(argumentsContainer->Right());
			if (!body) return Result("Expected function body to be an sexpression", argumentsContainer);

			auto newFunction = ValuePtr(new Macro(false, name, arguments, body));
			binding->Assign(name->String(), newFunction);
			return newFunction;
		}
	};
    
    void Functions::Initialize(BindingPtr binding)
    {
		NativeFunction::Initialize(binding, "function", new DefineFunction());
		NativeFunction::Initialize(binding, "eval", new EvalFunction());
		NativeFunction::Initialize(binding, "macro", new DefineMacro());
    }
}