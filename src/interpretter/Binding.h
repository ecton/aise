#pragma once

#include "AiseCommon.h"
#include "Value.h"
#include <unordered_map>
#include "Result.h"


namespace Aise {
  class Environment;

    class Binding : public std::enable_shared_from_this<Binding>
    {
    public:
        // Standard constructor
        Binding(Aise::Environment *environment);
        // Standard Destructor
        virtual ~Binding() { }
        
        virtual void Assign(std::string name, ValuePtr value);
        virtual ValuePtr Get(std::string name);

        Aise::Environment *Environment() { return mEnvironment; }
        virtual Result Interpret(ValuePtr expression, bool simplify = false);
    private:
        Aise::Environment *mEnvironment;
    std::unordered_map<std::string, ValuePtr> mTable;
    };
}