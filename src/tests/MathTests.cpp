#include "Catch.h"
#include "Aise.h"
#include "Environment.h"
#include "Integer.h"
#include "Real.h"
#include "Boolean.h"

using namespace std;
using namespace Aise;

TEST_CASE("Simple Addition", "[math][addition]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(add 1 2)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Integer>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == 3);
}

TEST_CASE("Simple Addition All Real", "[math][addition]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(add 1.1 2.2)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Real>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == Approx(3.3) );
}

TEST_CASE("Simple Addition Start Integer Result Real", "[math][addition]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(add 1 2.2)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Real>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == Approx(3.2) );
}

TEST_CASE("Simple Addition Start Real add Integer", "[math][addition]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(add 1.1 2)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Real>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == Approx(3.1) );
}

TEST_CASE("Simple Subtraction", "[math][subtraction]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(subtract 1 2)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Integer>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == -1);
}

TEST_CASE("Simple Subtraction All Real", "[math][subtraction]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(subtract 3.3 2.2)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Real>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == Approx(1.1) );
}

TEST_CASE("Simple Subtraction Start Integer Result Real", "[math][subtraction]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(subtract 3 2.2)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Real>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == Approx(0.8) );
}

TEST_CASE("Simple Subtraction Start Real add Integer", "[math][subtraction]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(subtract 3.1 2)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Real>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == Approx(1.1) );
}

TEST_CASE("Simple Multiplication", "[math][multiplication]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(multiply 3 2)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Integer>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == 6);
}

TEST_CASE("Simple Multiplication All Real", "[math][multiplication]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(multiply 3.3 2.2)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Real>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == Approx(7.26) );
}

TEST_CASE("Simple Multiplication Start Integer Result Real", "[math][multiplication]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(multiply 3 2.2)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Real>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == Approx(6.6) );
}

TEST_CASE("Simple Multiplication Start Real add Integer", "[math][multiplication]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(multiply 3.1 2)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Real>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == Approx(6.2) );
}

TEST_CASE("Simple Division", "[math][division]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(divide 3 2)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Integer>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == 1);
}

TEST_CASE("Simple Division All Real", "[math][division]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(divide 3.3 1.1)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Real>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == Approx(3.0) );
}

TEST_CASE("Simple Division Start Integer Result Real", "[math][division]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(divide 10 1.5)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Real>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == Approx(6.6666) );
}

TEST_CASE("Simple Division Start Real add Integer", "[math][division]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(divide 3.1 2)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Real>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == Approx(1.55) );
}

TEST_CASE("Simple Powers", "[math][power]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(power 3 2)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Integer>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == 9);
}

TEST_CASE("Simple Powers All Real", "[math][power]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(power 3.3 1.1)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Real>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == Approx(3.718479) );
}

TEST_CASE("Simple Powers Start Integer Result Real", "[math][power]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(power 2 1.5)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Real>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == Approx(2.828427) );
}

TEST_CASE("Simple Powers Start Real add Integer", "[math][power]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(power 3.1 2)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Real>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == Approx(9.61) );
}

TEST_CASE("Expressions - Literal first, function second", "[math][expressions]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(add 1 (subtract 3 2))");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Integer>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == 2);
}

TEST_CASE("Expressions - Funciton first, literal second", "[math][expressions]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(add (subtract 3 2) 1)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Integer>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == 2);
}

TEST_CASE("Expressions - Funciton first, function second", "[math][expressions]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(add (subtract 3 2) (subtract 5 2))");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Integer>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == 4);
}

TEST_CASE("Expressions - Multiple Nests, function second", "[math][expressions]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(add (subtract (power 2 2) 2) (subtract 5 2))");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Integer>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == 5);
}

TEST_CASE("Real Edges - infinity", "[math][infinity]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(infinity? (divide 1.0 0))");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Boolean>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() );
}

TEST_CASE("Real Edges - not a number", "[math][nan]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(nan? (divide 0.0 0.0))");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Boolean>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() );
}