// primes.cpp : Defines the entry point for the console application.
// Lab 2, task 4, variant 4: buil prime numbers set (<=upperBound)

#include "stdafx.h"
#include "primes.h"
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid number of arguments.\n";
		std::cout << "Usage: primes.exe <upperBound 1..10^8>\n";
		return 1;
	}

	int upperBound;
	if (!GetNumber(argv[1], upperBound))
	{
		std::cout << "Check argument.\n";
		std::cout << "Usage: primes.exe <upperBound 1..10^8>\n";
		return 1;
	}

	std::set<int> primes = GeneratePrimeNumbersSet(upperBound);
	std::cout << "There are " << primes.size() << " prime numbers\n";

	return 0;
}
