#pragma once

#include "Aise.h"
#include "Value.h"
#include <unordered_map>

namespace Aise {
    class Binding
    {
    public:
        // Standard constructor
        Binding() { }
        // Standard Destructor
        virtual ~Binding() { }
        
        void Assign(std::string name, ValuePtr value);
        ValuePtr Get(std::string name);
    private:
        std::unordered_map<std::string, ValuePtr> mTable;
    };
}