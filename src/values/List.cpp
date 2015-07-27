#include "List.h"
#include "Binding.h"
#include <sstream>

using namespace std;

namespace Aise {
	List::List(bool isTemplate) : Aise::Value(isTemplate)
	{
	}

	List::List(bool isTemplate, vector<ValuePtr> vector) : Aise::Value(isTemplate)
	{
		mVector = vector;
	}

	List::~List()
	{
	}
    
    string List::Description()
    {
		stringstream out;
		out << "[";
		for (size_t i = 0; i < mVector.size(); i++) {
			if (i > 0) out << ", ";
			out << mVector[i]->Description();
		}
		out << "]";
		return out.str();
	}

	int List::Compare(ValuePtr to)
	{
		auto otherCasted = dynamic_pointer_cast<List>(to);
		if (!otherCasted) return -1;

		for (size_t i = 0; i < mVector.size(); i++) {
			if (i >= otherCasted->mVector.size()) return 1;
			// TODO: Deal with null
			int result = mVector[i]->Compare(otherCasted->mVector[i]);
			if (result != 0) return result;
		}

		if (mVector.size() < otherCasted->mVector.size()) return -1;
		return 0;
	}

	Result List::EvaluateTemplate(BindingPtr binding)
	{
		auto newList = new List(false);
		for (size_t i = 0; i < mVector.size(); i++) {
			auto result = mVector[i]->EvaluateTemplate(binding);
			if (result.Error()) return result;
			newList->Push(result.Value());
		}
		return ValuePtr(newList);
	}

	Result List::Pop()
	{
		if (mVector.size() == 0) return Result("Out Of Bounds", dynamic_pointer_cast<Value>(shared_from_this()));

		ValuePtr last = mVector[mVector.size() - 1];
		mVector.pop_back();
		return last;
	}

	Result List::Get(size_t index)
	{
		if (index >= mVector.size()) return Result("Out Of Bounds", dynamic_pointer_cast<Value>(shared_from_this()));

		return mVector[index];
	}
  
  Result List::Remove(size_t index)
  {
    if (index >= mVector.size()) return Result("Out Of Bounds", dynamic_pointer_cast<Value>(shared_from_this()));

    ValuePtr value = mVector[index];
    mVector.erase(mVector.begin() + index);
    return value;
  }

  Result List::Insert(size_t index, ValuePtr value)
  {
    if (index > mVector.size()) return Result("Out Of Bounds", dynamic_pointer_cast<Value>(shared_from_this()));

    mVector.insert(mVector.begin() + index, value);
    return value;
  }
}
