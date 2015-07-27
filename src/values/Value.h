#pragma once
#include "AiseCommon.h"

namespace Aise {
  class Binding; 
  class Result;
  class Value
  {
  public:
    virtual ~Value() { }
        virtual std::string Description() = 0;
    static ValuePtr Simplify(BindingPtr binding, ValuePtr value);
    virtual int Compare(ValuePtr to) = 0;
    bool IsTemplate() {
      return mTemplate;
    }
    virtual Result EvaluateTemplate(BindingPtr binding) = 0;

    virtual std::string Name() { return "Value"; }

    // Collections
    virtual Result Get(BindingPtr binding, std::vector<ValuePtr> arguments);
    virtual Result Push(BindingPtr binding, std::vector<ValuePtr> arguments);
    virtual Result Pop(BindingPtr binding, std::vector<ValuePtr> arguments);
    virtual Result Count(BindingPtr binding);
    virtual Result Remove(BindingPtr binding, std::vector<ValuePtr> arguments);
    virtual Result Insert(BindingPtr binding, std::vector<ValuePtr> arguments);
  protected:
    Value(bool isTemplate) : mTemplate(isTemplate) { }
    bool mTemplate;
    };
};
