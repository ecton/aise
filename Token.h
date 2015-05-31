#pragma once
#include "Aise.h"
#include "Source.h"

namespace Aise {
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
        TokenType Type() { return mType; }
        Token(TokenType type, std::shared_ptr<Source> src, int offset, int length, int line, int col)
        : mType(type), mSrc(src), mOffset(offset), mLength(length), mLine(line), mCol(col) { }
        
        int Offset() { return mOffset; }
        int Length() { return mLength; }
        int Line() { return mLine; }
        int Column() { return mCol; }
        std::string String() { return mSrc->Src()->substr(mOffset, mLength); }
    private:
        int mOffset, mLength, mLine, mCol;
        std::shared_ptr<Source> mSrc;
        TokenType mType;
    };
}