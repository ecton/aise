#include "Tokenizer.h"

using namespace std;

#define IS_IDENTIFIER(chr) ((chr >= 'a' && chr <= 'z') || \
                           (chr >= 'A' && chr <= 'Z') || \
                           (chr >= '0' && chr <= '9') || \
                            chr == '-' || chr == '_' || chr == '?')

namespace Aise {
    Tokenizer::Tokenizer(shared_ptr<Source> source) : mPosition(-1)
	{
        int pos = 0;
        int lineStart = 0;
        int lineNum = 1;
        const string *src = source->Src().get();
        
        while (pos < src->length()) {
            if (src->at(pos) == ' ' || src->at(pos) == '\t') {
                pos++;
            } else if (src->at(pos) == '\r' || src->at(pos) == '\n') {
                if (src->at(pos) == '\r' && pos + 1 < src->length() && src->at(pos+1) == '\n') {
                    pos++;
                }
                pos++;
                lineStart = pos;
                lineNum++;
            } else if (IS_IDENTIFIER(src->at(pos))) {
                int start = pos;
                while (pos < src->length() && IS_IDENTIFIER(src->at(pos))) {
                    pos++;
                }
                mTokens.push_back(Token(Token::TYPE_IDENTIFIER, source, start, pos - start, lineNum, pos - lineStart));
            } else if (src->at(pos) == '(') {
                mTokens.push_back(Token(Token::TYPE_OPEN_PAREN, source, pos, 1, lineNum, pos - lineStart));
                pos++;
            } else if (src->at(pos) == ')') {
                mTokens.push_back(Token(Token::TYPE_CLOSE_PAREN, source, pos, 1, lineNum, pos - lineStart));
                pos++;
            } else {
                throw "Unknown character";
            }
        }
    }
    
    bool Tokenizer::EndOfInput() {
        return mPosition + 1 == mTokens.size();
    }
    
    Token &Tokenizer::Next() {
        mPosition++;
        return mTokens.at(mPosition);
    }
    
    Token &Tokenizer::Peek(int offset) {
        return mTokens[mPosition + offset];
    }


	Tokenizer::~Tokenizer()
	{
	}
}