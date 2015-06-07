#include "Catch.h"
#include "Aise.h"
#include "Environment.h"
#include "Integer.h"
#include "Real.h"
#include "Boolean.h"

using namespace std;
using namespace Aise;

TEST_CASE("If - Simple if, no else", "[flow][if]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(if true 5)");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Integer>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == 5);
}

TEST_CASE("If - Simple if, no else, false", "[flow][if]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(if false 5)");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Boolean>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == false);
}

TEST_CASE("If - Simple if, else, false", "[flow][if]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(if false 5 else 4)");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Integer>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == 4);
}

TEST_CASE("If - Complex if, else, true", "[flow][if]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(if (nan? (divide 0.0 0.0)) (5) else (4))");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Integer>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == 5);
}

TEST_CASE("If - Complex if, else, false", "[flow][if]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(if (nan? (divide 1.0 0.0)) (5) else (4))");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Integer>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == 4);
}

TEST_CASE("If - nested if -- else if", "[flow][if]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(if false 5 else if true 4)");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Integer>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == 4);
}

TEST_CASE("If - nested if -- else if else", "[flow][if]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(if false 5 else if false 4 else 2)");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Integer>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == 2);
}

TEST_CASE("equals - real", "[flow][equals][real]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(equals 1.1 1.1)");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Boolean>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == true);
}

TEST_CASE("equals - real negative", "[flow][equals][real]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(equals 1.2 1.1)");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Boolean>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == false);
}

TEST_CASE("less-than - real", "[flow][equals][real]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(less-than 1.1 1.2)");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Boolean>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == true);
}

TEST_CASE("less-than - real negative", "[flow][equals][real]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(less-than 1.3 1.2)");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Boolean>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == false);
}

TEST_CASE("less-than-or-equal - real", "[flow][equals][real]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(less-than-or-equal 1.1 1.2)");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Boolean>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == true);
}

TEST_CASE("less-than-or-equal - real negative", "[flow][equals][real]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(less-than-or-equal 1.3 1.2)");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Boolean>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == false);
}

TEST_CASE("less-than-or-equal - real equal", "[flow][equals][real]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(less-than-or-equal 1.2 1.2)");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Boolean>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == true);
}

TEST_CASE("greater-than - real", "[flow][equals][real]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(greater-than 1.2 1.1)");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Boolean>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == true);
}

TEST_CASE("greater-than - real negative", "[flow][equals][real]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(greater-than 1.1 1.2)");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Boolean>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == false);
}

TEST_CASE("greater-than-or-equal - real", "[flow][equals][real]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(greater-than-or-equal 1.3 1.2)");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Boolean>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == true);
}

TEST_CASE("greater-than-or-equal - real negative", "[flow][equals][real]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(greater-than-or-equal 1.1 1.2)");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Boolean>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == false);
}

TEST_CASE("greater-than-or-equal - real equal", "[flow][equals][real]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(greater-than-or-equal 1.2 1.2)");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Boolean>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == true);
}


TEST_CASE("Loop to 10", "[loop][set]") {
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(do (set x 0) (while (less-than x 10) (set x (add x 1)))");
	REQUIRE(result.Error() == false);
	auto value = dynamic_pointer_cast<Integer>(result.Value());
	REQUIRE(value);
	REQUIRE(value->Value() == 10);
}