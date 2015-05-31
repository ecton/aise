#pragma once
#include "Aise.h"

namespace Aise {
	class Tokenizer
	{
	public:
		class Token 
		{
		public: 
			typedef enum {
				TYPE_EOF = 0,
				TYPE_OPEN_PAREN,
				TYPE_CLOSE_PAREN,
				TYPE_IDENTIFIER,
				TYPE_NUMERIC,
				TYPE_STRING
			} TokenType;
			TokenType Type();
			Token(TokenType type, StringPtr src, int offset, int length, int line, int col) : mOffset(offset), mLength(length) { }
		private:
			int mOffset, mLength, mLine, mCol;
			StringPtr mSrc;
			TokenType mType;
		};
		Tokenizer(StringPtr src);
		~Tokenizer();
	private:
		std::string::iterator mIterator;
	};
}