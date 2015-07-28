#pragma once

#include "AiseCommon.h"
#include "Value.h"

namespace Aise {
  class Source
  {
  public:
    Source(std::string name, StringPtr src) { mName = name; mSrc = src; }
    Source() { }
    ~Source() { }
    std::string Name() { return mName; }
    StringPtr Src() { return mSrc; }
    ValuePtr Sexp() { return mSexp; }
    void SetSexp(ValuePtr sexp) { mSexp = sexp; }
  private:
    std::string mName;
    StringPtr mSrc;
    ValuePtr mSexp;
  };
}