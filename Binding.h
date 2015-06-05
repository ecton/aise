#pragma once

#include "Aise.h"
#include "Value.h"
#include <unordered_map>


namespace Aise {
	class Environment;

    class Binding
    {
    public:
        // Standard constructor
        Binding(Environment *environment) : mEnvironment(environment) { }
        // Standard Destructor
        virtual ~Binding() { }
        
        void Assign(std::string name, ValuePtr value);
        ValuePtr Get(std::string name);

		Environment *Environment() { return mEnvironment; }
    private:
		class Environment *mEnvironment;
		std::unordered_map<std::string, ValuePtr> mTable;
    };

	typedef std::shared_ptr<Binding> BindingPtr;
}