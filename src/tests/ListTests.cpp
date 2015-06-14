#include "Catch.h"
#include "Aise.h"

using namespace std;
using namespace Aise;

TEST_CASE("Lists - Simple list", "[lists]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("([1, 2])");
	INFO(result.ErrorMessage());
	REQUIRE(result.Error() == false);
	auto container = dynamic_pointer_cast<SExp>(result.Value());
	REQUIRE(container);
	auto value = dynamic_pointer_cast<List>(container->Left());
	REQUIRE(value);
	REQUIRE(value->Count() == 2);
}

TEST_CASE("Lists - Simple list, trailing comma", "[lists]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("([1, 2, ])");
	INFO(result.ErrorMessage());
	REQUIRE(result.Error() == false);
	auto container = dynamic_pointer_cast<SExp>(result.Value());
	REQUIRE(container);
	auto value = dynamic_pointer_cast<List>(container->Left());
	REQUIRE(value);
	REQUIRE(value->Count() == 2);
}

TEST_CASE("Lists - Embedded List, trailing comma", "[lists]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("([1, [2, 3]])");
	INFO(result.ErrorMessage());
	REQUIRE(result.Error() == false);
	auto container = dynamic_pointer_cast<SExp>(result.Value());
	REQUIRE(container);
	auto value = dynamic_pointer_cast<List>(container->Left());
	REQUIRE(value);
	REQUIRE(value->Count() == 2);
}

TEST_CASE("Lists - SExpression inside, trailing comma", "[lists]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("([1, ([2, 3] [3,2])])");
	INFO(result.ErrorMessage());
	REQUIRE(result.Error() == false);
	auto container = dynamic_pointer_cast<SExp>(result.Value());
	REQUIRE(container);
	auto value = dynamic_pointer_cast<List>(container->Left());
	REQUIRE(value);
	REQUIRE(value->Count() == 2);
}