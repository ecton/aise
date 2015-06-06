#include "Result.h"

using namespace std;

namespace Aise {
	Result::Result(string message, ValuePtr where) {
		mError = true;
		mMessage = message;
        mValue = where;
    }

	Result::Result(ValuePtr value) {
		mError = false;
		mValue = value;
	}

	Result::~Result()
	{

	}
}