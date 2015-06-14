#pragma once
#include "AiseCommon.h"
#include "Environment.h"
#include "Token.h"

namespace Aise {
	class Tokenizer
	{
	public:
        Tokenizer(std::shared_ptr<Source> src);
		~Tokenizer();
        
        bool EndOfInput();
        std::shared_ptr<Token> Next();
		std::shared_ptr<Token> Peek(size_t offset = 1);
        
	private:
        std::vector<std::shared_ptr<Token>> mTokens;
		size_t mPosition;
	};
}