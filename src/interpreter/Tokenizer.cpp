#include "Tokenizer.h"
#include <sstream>

using namespace std;

#define IS_IDENTIFIER(chr) ((chr >= 'a' && chr <= 'z') || \
                            (chr >= 'A' && chr <= 'Z') || \
                            chr == '-' || chr == '_' || chr == '?')

#define IS_NUMERIC(chr) (chr >= '0' && chr <= '9')

namespace Aise {
  Tokenizer::Tokenizer(shared_ptr<Source> source) : mPosition(-1)
  {
    size_t pos = 0;
    size_t lineStart = 0;
    size_t lineNum = 1;
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
        size_t start = pos;
        while (pos < src->length() && (IS_IDENTIFIER(src->at(pos)) || IS_NUMERIC(src->at(pos)))) {
          pos++;
        }
        mTokens.push_back(shared_ptr<Token>(new Token(Token::TYPE_IDENTIFIER, source, start, pos - start, lineNum, pos - lineStart)));
      } else if (IS_NUMERIC(src->at(pos)) ||
       (src->at(pos) == '-' && pos + 1 < src->length() && IS_NUMERIC(src->at(pos + 1)))) {
        size_t start = pos;
        pos++;
        // Handle the integer part
        while (pos < src->length() && IS_NUMERIC(src->at(pos))) {
          pos++;
        }
        // Check for a decimal
        if (pos < src->length() && src->at(pos) == '.') {
          pos++;
          while (pos < src->length() && IS_NUMERIC(src->at(pos))) {
            pos++;
          }
          mTokens.push_back(shared_ptr<Token>(new Token(Token::TYPE_REAL, source, start, pos - start, lineNum, pos - lineStart)));
        } else {
          mTokens.push_back(shared_ptr<Token>(new Token(Token::TYPE_INTEGER, source, start, pos - start, lineNum, pos - lineStart)));
        }
      } else if (src->at(pos) == '"') {
        // String parsing. 
        size_t start = pos;
        pos++;
        stringstream parsed;
        while (pos < src->length() && src->at(pos) != '"') {
          if (src->at(pos) == '\\') {
            pos++;
            if (pos >= src->length()) throw "Expected more after escape character.";
            switch (src->at(pos)) {
              case '\\':
              case '/':
              case '"': { parsed << src->at(pos); pos++; } break;
              case 'b': { parsed << '\b'; pos++; } break;
              case 'f': { parsed << '\f'; pos++; } break;
              case 'n': { parsed << '\n'; pos++; } break;
              case 'r': { parsed << '\r'; pos++; } break;
              case 't': { parsed << '\t'; pos++; } break;
              case 'u': throw "Unicode not yet supported.";
              default: throw "Unknown escape character.";
            }
          } else if (src->at(pos) < 32) {
            throw "Invalid character.";
          } else {
            parsed << src->at(pos);
            pos++;
          }
        }
        pos++; // Skip the trailing quote
        mTokens.push_back(shared_ptr<Token>(new Token(Token::TYPE_STRING, source, parsed.str(), start, pos - start, lineNum, pos - lineStart)));
      } else if (src->at(pos) == '(') {
        mTokens.push_back(shared_ptr<Token>(new Token(Token::TYPE_OPEN_PAREN, source, pos, 1, lineNum, pos - lineStart)));
        pos++;
      } else if (src->at(pos) == ')') {
        mTokens.push_back(shared_ptr<Token>(new Token(Token::TYPE_CLOSE_PAREN, source, pos, 1, lineNum, pos - lineStart)));
        pos++;
      } else if (src->at(pos) == '`') {
        mTokens.push_back(shared_ptr<Token>(new Token(Token::TYPE_BACKTICK, source, pos, 1, lineNum, pos - lineStart)));
        pos++;
      }
      else if (src->at(pos) == ',') {
        mTokens.push_back(shared_ptr<Token>(new Token(Token::TYPE_COMMA, source, pos, 1, lineNum, pos - lineStart)));
        pos++;
      }
      else if (src->at(pos) == '[') {
        mTokens.push_back(shared_ptr<Token>(new Token(Token::TYPE_OPEN_BRACKET, source, pos, 1, lineNum, pos - lineStart)));
        pos++;
      }
      else if (src->at(pos) == ']') {
        mTokens.push_back(shared_ptr<Token>(new Token(Token::TYPE_CLOSE_BRACKET, source, pos, 1, lineNum, pos - lineStart)));
        pos++;
      }
      else if (src->at(pos) == '{') {
        mTokens.push_back(shared_ptr<Token>(new Token(Token::TYPE_OPEN_BRACE, source, pos, 1, lineNum, pos - lineStart)));
        pos++;
      }
      else if (src->at(pos) == '}') {
        mTokens.push_back(shared_ptr<Token>(new Token(Token::TYPE_CLOSE_BRACE, source, pos, 1, lineNum, pos - lineStart)));
        pos++;
      } else {
        throw "Unknown character";
      }
    }
  }
  
  bool Tokenizer::EndOfInput() {
    return mPosition + 1 == mTokens.size();
  }
  
  shared_ptr<Token> Tokenizer::Next() {
    mPosition++;
    return mTokens.at(mPosition);
  }
  
  shared_ptr<Token> Tokenizer::Peek(size_t offset) {
    return mTokens[mPosition + offset];
  }


  Tokenizer::~Tokenizer()
  {
  }
}
