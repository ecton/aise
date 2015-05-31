#include "Environment.h"

using namespace std;

namespace Aise {
	Environment::Environment()
	{
	}


	Environment::~Environment()
	{
	}

	void Environment::AddSource(string name, const std::string &src)
	{
		mSources[name] = Source(name, StringPtr(new string(src)));
	}

	ValuePtr Evaluate()
	{
		return NULL;
	}
}