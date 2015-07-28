#include "Catch.h"
#include "Aise.h"

using namespace std;
using namespace Aise;

TEST_CASE("Simple string parsing", "[strings][parsing]") {
  auto env = new Aise::Environment();
  Aise::Result result = env->Evaluate("(\"test\")");
  INFO( result.ErrorMessage() );
  REQUIRE( result.Error() == false );
  auto container = dynamic_pointer_cast<SExp>(result.Value());
  REQUIRE( container );
  auto value = dynamic_pointer_cast<String>(container->Left());
  REQUIRE( value );
  REQUIRE( value->Value().compare("test") == 0 );
}
