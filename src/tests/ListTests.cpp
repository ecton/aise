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

TEST_CASE("Lists - get", "[lists][get]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(get [10, 20] 1)");
	INFO(result.ErrorMessage());
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Integer>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == 20);
}

TEST_CASE("Lists - push", "[lists][push][get]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(do (set x [10, 20]) (push x 30) (get x 2))");
	INFO(result.ErrorMessage());
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Integer>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == 30);
}

TEST_CASE("Lists - pop", "[lists][pop]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(pop [10, 20])");
	INFO(result.ErrorMessage());
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Integer>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == 20);
}

TEST_CASE("Lists - count", "[lists][pop]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(count [10, 20])");
	INFO(result.ErrorMessage());
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Integer>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == 2);
}


TEST_CASE("Lists - insert at 0", "[lists][insert]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(do (set x [2, 3]) (insert x 0 1) (get x 0))");
	INFO(result.ErrorMessage());
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Integer>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == 1);
}

TEST_CASE("Lists - insert as append", "[lists][insert]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(do (set x [1, 2]) (insert x 2 3) (get x 2))");
	INFO(result.ErrorMessage());
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Integer>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == 3);
}

TEST_CASE("Lists - remove", "[lists][remove]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(do (set x [1, 2, 3]) (remove x 1) (get x 1))");
	INFO(result.ErrorMessage());
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Integer>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == 3);
}
