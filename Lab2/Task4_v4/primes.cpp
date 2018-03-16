// primes.cpp : Defines the entry point for the console application.
// Lab 2, task 4, variant 4

#include "stdafx.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>

using namespace std;
const size_t upperMaxBound = 100000000;

bool GetNumber(const string& str, int& number)
{
	size_t stoppedAt;
	number = 0;
	try
	{
		number = stoi(str, &stoppedAt);
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
/*
set<int> GeneratePrimeNumbersSet(int upperBound)
{
	set<int> primes;
	vector<bool> sieve(upperBound + 1);
	fill(sieve.begin(), sieve.end(), true);
	sieve.at(0) = sieve.at(1) = false;
	int step = 1;
	for (int number = 2; number <= upperBound; number++)
	{
		if (sieve.at(number))
		{
			primes.emplace(number);
			if (number > upperBound / number)
				continue;
			for (int notPrime = number * number; notPrime <= upperBound; notPrime += number)
			{
				sieve.at(notPrime) = false;
				if (notPrime > upperBound - number)
					break;
			}
		}
	}
	return primes;
}*/

set<int> GeneratePrimeNumbersSet(int upperBound)
{
	set<int> primes;
	vector<bool> sieve(upperBound + 1);
	fill(sieve.begin(), sieve.end(), true);
	sieve.at(0) = sieve.at(1) = false;
	sieve.at(2) = true;
	primes.emplace(2);
	for (int number = 3; number <= upperBound; number += 2)
	{
		if (sieve.at(number))
		{
			primes.emplace(number);
			sieve.at(number) = false;
		}
		for (auto prime : primes)
		{
			if (prime > number || number > upperBound / prime)
				break;
			sieve.at(prime * number) = false;
			if (number % prime == 0)
				break;
		}
	}
	return primes;
}

void CopyPrimesToCout(const set<int>& primes)
{
	copy(primes.begin(), primes.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid number of arguments.\n";
		cout << "Usage: primes.exe <upperBound 1..10^8>\n";
		return 1;
	}

	int upperBound;
	if (!GetNumber(argv[1], upperBound))
	{
		cout << "Check argument.\n";
		cout << "Usage: primes.exe <upperBound 1..10^8>\n";
		return 1;
	}

	set<int> primes = GeneratePrimeNumbersSet(upperBound);
	cout << "There are " << primes.size() << " prime numbers\n";

	//CopyPrimesToCout(primes);

	return 0;
}
