// aise.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include "Environment.h"
#define CATCH_CONFIG_RUNNER
#include "Catch.h"

//#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
//#define ARGVTYPE wchar_t
//#define main wmain
//#else
//#define ARVTYYPE char_t
//#endif

using namespace std;

int main(int argc, const char *argv[])
{
	cout << "Running" << endl;
	auto env = new Aise::Environment();
	Aise::Result result = env->Evaluate("(do (function mul-by-5 (x) (multiply x 5)) (mul-by-5 3))");
	if (result.Error()) {
		cout << "Error: " << result.ErrorMessage() << " at " << result.Value()->Description() << endl;
	}
	else {
		cout << "Result: " << result.Value()->Description() << endl;
	}
	getchar();
/*    int result = Catch::Session().run();
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	getchar();
#endif*/
	return 0;
    

//	getchar();
//
//	return 0;
}

