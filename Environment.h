#pragma once

#include "Aise.h"
#include <map>
#include "Source.h"

namespace Aise {
	class Environment
	{
    public:
		Environment();
		virtual ~Environment();
		void AddSource(std::string name, const std::string &src);
        ValuePtr Evaluate(const std::string &main);
	private:
        std::map<std::string, std::shared_ptr<Source>> mSources;
        ValuePtr Parse(std::shared_ptr<Source> source);
    };
}