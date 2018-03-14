// primes.cpp : Defines the entry point for the console application.
// Lab 2, task 4, variant 4

#include "stdafx.h"
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;
const size_t upperMaxBound = 100000000;

bool GetNumber(const string & str, int & number)
{
	size_t stoppedAt;
	number = 0;
	try
	{
		int number = stoi(str, &stoppedAt);
		if (number < 1 || number > upperMaxBound)
		{
			return false;
		}
		if (stoppedAt != str.length())
		{
			return false;
		}
		return true;
	}
	catch (const std::out_of_range)
	{
		return false;
	}
	catch (const std::invalid_argument)
	{
		return false;
	}
}


int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "Invalid number of arguments.\n";
		cout << "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}

	int upperBound;
	if (!GetNumber(argv[1], upperBound))
	{
		cout << "Check argument.\n";
		cout << "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}

	return 0;
}

