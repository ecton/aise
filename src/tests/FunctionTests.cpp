#include "Catch.h"
#include "Aise.h"

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
  REQUIRE(value->Value() == 3);
}

TEST_CASE("Simple Macro - increment", "[functions][macro]") {
  auto env = new Aise::Environment();
  Aise::Result result = env->Evaluate("(do (macro incr (x) `(add ,x 1)) (incr 5))");
  REQUIRE(result.Error() == false);
  auto value = dynamic_pointer_cast<Integer>(result.Value());
  REQUIRE(value);
  REQUIRE(value->Value() == 6);
}

TEST_CASE("Simple Macro - increment increment", "[functions][macro]") {
  auto env = new Aise::Environment();
  Aise::Result result = env->Evaluate("(do (macro incr (x) `(add ,x 1)) (incr (incr 5)))");
  REQUIRE(result.Error() == false);
  auto value = dynamic_pointer_cast<Integer>(result.Value());
  REQUIRE(value);
  REQUIRE(value->Value() == 7);
}

TEST_CASE("Simple Macro - Namespace test -- macro parameter properly set", "[functions][macro]") {
  auto env = new Aise::Environment();
  Aise::Result result = env->Evaluate("(do (set x 2) (macro incr (x) `(add ,x 1)) (incr 5))");
  REQUIRE(result.Error() == false);
  auto value = dynamic_pointer_cast<Integer>(result.Value());
  REQUIRE(value);
  REQUIRE(value->Value() == 6);
}

TEST_CASE("Simple Macro - Namespace test -- macro doesn't overwrite local context", "[functions][macro]") {
  auto env = new Aise::Environment();
  Aise::Result result = env->Evaluate("(do (set x 2) (macro incr (x) `(add ,x 1)) (incr 5) x)");
  REQUIRE(result.Error() == false);
  auto value = dynamic_pointer_cast<Integer>(result.Value());
  REQUIRE(value);
  REQUIRE(value->Value() == 2);
}