#pragma once

#include "AiseCommon.h"
#include <map>
#include "Source.h"
#include "Binding.h"
#include "Result.h"
#include "Symbol.h"
#include "SExp.h"

namespace Aise {
    /* Aise interpretter class
     *
     * This class encapsulates the logic for the base Aise interpretter. 
     */
     
	class Environment
	{
    public:
        // Standard constructor
		Environment();
        // Standard Destructor
		virtual ~Environment();
        
        // Adds a chunk of Aise source, and associates it with a name to be loaded from
		void AddSource(std::string name, const std::string &src);
        // Evaluates a chunk of Aise source, including any sources previously added if needed
        Result Evaluate(const std::string &main);

		BindingPtr EnterBinding();
		void ExitBinding();
		Result Interpret(BindingPtr binding, ValuePtr expression);
        
        ValuePtr TrueValue();
        ValuePtr FalseValue();
	private:
        std::map<std::string, std::shared_ptr<Source>> mSources;
        std::vector<BindingPtr> mBindingStack;
		BindingPtr Globals() { return mBindingStack[0]; }
        
        Result Parse(std::shared_ptr<Source> source);
        Result Invoke(BindingPtr binding, ValuePtr method, SExpPtr expression);
        Result LookupAndInvoke(BindingPtr binding, SymbolPtr symbol, SExpPtr expression);
        Result Lookup(BindingPtr binding, SymbolPtr symbol, ValuePtr expression);
    };
}