// aise.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include "Environment.h"

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
    Aise::ValuePtr result = env->Evaluate("(add 1 (subtract 2 3) 4 5)");
    cout << "Result: " << result->Description() << endl;
	getchar();

	return 0;
}

