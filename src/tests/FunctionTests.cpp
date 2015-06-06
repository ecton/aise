#include "Catch.h"
#include "Aise.h"
#include "Environment.h"
#include "Integer.h"
#include "Real.h"
#include "Boolean.h"

using namespace std;
using namespace Aise;

TEST_CASE("Simple Function - static result", "[functions][do]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(do (function return-5 () 5) (return-5))");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Integer>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == 5);
}