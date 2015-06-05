#pragma once

#include "Aise.h"
#include <map>
#include "Source.h"
#include "Binding.h"

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
        ValuePtr Evaluate(const std::string &main);

		BindingPtr EnterBinding();
		void ExitBinding();
	private:
        std::map<std::string, std::shared_ptr<Source>> mSources;
        std::vector<BindingPtr> mBindingStack;
		BindingPtr Globals() { return mBindingStack[0]; }
        
        ValuePtr Parse(std::shared_ptr<Source> source);
        ValuePtr Interpret(BindingPtr binding, ValuePtr expression);
    };
}