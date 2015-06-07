#include "Catch.h"
#include "Aise.h"
#include "Environment.h"
#include "Integer.h"
#include "Real.h"
#include "Boolean.h"

using namespace std;
using namespace Aise;

TEST_CASE("Simple Function - static result", "[functions][do]") {\
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(do (function return-5 () 5) (return-5))");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Integer>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == 5);
}

TEST_CASE("Simple Function - accept one parameter", "[functions][do]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(do (function multiply-by-5 (x) (multiply x 5)) (multiply-by-5 4))");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Integer>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == 20);
}

TEST_CASE("Simple Function - operate on two parameters", "[functions][do]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(do (function average (x y) (divide (add x y) 2)) (average 2 4))");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Integer>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == 2);
}