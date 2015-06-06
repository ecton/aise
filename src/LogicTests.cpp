#include "Catch.h"
#include "Aise.h"
#include "Environment.h"
#include "Boolean.h"

using namespace std;
using namespace Aise;

TEST_CASE("And - True False", "[logic][and]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(and true false)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Boolean>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == false );
}

TEST_CASE("And - True True", "[logic][and]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(and true true)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Boolean>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == true );
}

TEST_CASE("And - false True", "[logic][and]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(and false true)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Boolean>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == false );
}

TEST_CASE("And - true nan?", "[logic][and]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(and true (nan? (divide 0.0 0.0)))");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Boolean>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == true );
}

TEST_CASE("Or - True False", "[logic][or]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(or true false)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Boolean>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == true );
}

TEST_CASE("Or - false false", "[logic][or]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(or false false)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Boolean>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == false );
}

TEST_CASE("Or - false True", "[logic][or]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(or false true)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Boolean>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == true );
}

TEST_CASE("Or - false nan?", "[logic][or]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(or false (nan? (divide 0.0 0.0)))");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Boolean>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == true );
}

TEST_CASE("Not - true", "[logic][not]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(not true)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Boolean>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == false );
}

TEST_CASE("Not - false", "[logic][not]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(not false)");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Boolean>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == true );
}

TEST_CASE("Not - Not true", "[logic][not]") {
    auto env = new Aise::Environment();
    Aise::Result result = env->Evaluate("(not (not true))");
    REQUIRE( result.Error() == false );
    auto value = dynamic_pointer_cast<Boolean>(result.Value());
    REQUIRE( value );
    REQUIRE( value->Value() == true );
}