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

    int result = Catch::Session().run();
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	getchar();
#endif
	return result;
}

