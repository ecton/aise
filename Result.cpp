#include "Result.h"

using namespace std;

namespace Aise {
	Result::Result(string message) {
		mError = true;
		mMessage = message;
	}

	Result::Result(ValuePtr value) {
		mError = false;
		mValue = value;
	}

	Result::~Result()
	{

	}
}