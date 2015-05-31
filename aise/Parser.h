#pragma once

#include "Aise.h"

using namespace std;

namespace Aise
{
	class Parser
	{
	public:
		Parser(Environment *env, string name, string src);
		~Parser();
	};
}