#include "Catch.h"
#include "Aise.h"
#include "Environment.h"
#include "Integer.h"
#include "Real.h"

using namespace std;
using namespace Aise;

#pragma mark Simple Addition

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

#pragma mark Simple Subtraction

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

#pragma mark Simple Multiplication

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

#pragma mark Simple Division

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