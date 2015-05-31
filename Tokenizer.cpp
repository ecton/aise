#include "Tokenizer.h"

using namespace std;

namespace Aise {
	Tokenizer::Tokenizer(StringPtr src)
	{
		mIterator = src.get()->begin();
	}


	Tokenizer::~Tokenizer()
	{
	}
}