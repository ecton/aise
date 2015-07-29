#pragma once
#include "AiseCommon.h"
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
      TYPE_REAL,
      TYPE_INTEGER,
      TYPE_STRING,
      TYPE_BACKTICK,
      TYPE_COMMA,
      TYPE_OPEN_BRACKET,
      TYPE_CLOSE_BRACKET,
      TYPE_OPEN_BRACE,
      TYPE_CLOSE_BRACE
    } TokenType;
    static bool TypeIsLiteral(TokenType type) {
      switch (type) {
        case TYPE_IDENTIFIER:
        case TYPE_REAL:
        case TYPE_INTEGER:
        case TYPE_STRING:
        return true;
        default:
        return false;
      }
    }
    
    TokenType Type() { return mType; }
    Token(TokenType type, std::shared_ptr<Source> src, size_t offset, size_t length, size_t line, size_t col)
    : mType(type), mSrc(src), mOffset(offset), mLength(length), mLine(line), mCol(col) { mValue = src->Src()->substr(offset, length); }
    Token(TokenType type, std::shared_ptr<Source> src, std::string value, size_t offset, size_t length, size_t line, size_t col) : mType(type), mSrc(src), mOffset(offset), mLength(length), mLine(line), mCol(col), mValue(value) { }
    
    size_t Offset() { return mOffset; }
    size_t Length() { return mLength; }
    size_t Line() { return mLine; }
    size_t Column() { return mCol; }
    std::string String() { return mValue; }
  private:
    size_t mOffset, mLength, mLine, mCol;
    std::string mValue;
    std::shared_ptr<Source> mSrc;
    TokenType mType;
  };
}
