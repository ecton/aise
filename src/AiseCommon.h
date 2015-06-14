#include <memory>
#include <string>
#include <vector>

namespace Aise {
	typedef std::shared_ptr<std::string> StringPtr;
	class Binding;
	typedef std::shared_ptr<Aise::Binding> BindingPtr;
	class SExp;
	typedef std::shared_ptr<Aise::SExp> SExpPtr;
	class Symbol;
	typedef std::shared_ptr<Aise::Symbol> SymbolPtr;
	class Value;
	typedef std::shared_ptr<Aise::Value> ValuePtr;
}