#pragma once
#include "Aise.h"
#include "Environment.h"
#include "Token.h"

namespace Aise {
	class Tokenizer
	{
	public:
        Tokenizer(std::shared_ptr<Source> src);
		~Tokenizer();
        
        bool EndOfInput();
        Token &Next();
        Token &Peek(int offset = 1);
        
	private:
        std::vector<Token> mTokens;
        int mPosition;
	};
}