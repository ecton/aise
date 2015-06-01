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
	private:
        std::map<std::string, std::shared_ptr<Source>> mSources;
        Binding mGlobals;
        std::vector<std::shared_ptr<Binding>> mBindingStack;
        
        ValuePtr Parse(std::shared_ptr<Source> source);
        ValuePtr Interpret(ValuePtr expression);
    };
}