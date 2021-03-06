// primes.cpp : Defines the entry point for the console application.
// Lab 2, task 4, variant 4

#include "stdafx.h"
#include "primes.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>

bool GetNumber(std::string const& str, int& number)
{
	size_t stoppedAt;
	number = 0;
	try
	{
		number = stoi(str, &stoppedAt);
		if (number < 1 || number > upperBoundMax)
		{
			return false;
		}
		if (stoppedAt != str.length())
		{
			return false;
		}
		return true;
	}
	catch (const std::out_of_range&)
	{
		return false;
	}
	catch (const std::invalid_argument&)
	{
		return false;
	}
}

std::vector<bool> GenerateSieve(int upperBound)
{
	if (upperBound < 0)
		upperBound = 0;
	std::vector<bool> sieve(upperBound + 1, true);
	sieve[0] = false;
	if (upperBound > 0)
		sieve[1] = false;

	for (int number = 2; number <= upperBound / number; number++)
	{
		if (sieve[number])
		{

			for (int numberToUncheck = number * number; numberToUncheck <= upperBound; numberToUncheck += number)
				sieve[numberToUncheck] = false;
		}
	}
	return sieve;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::set<int> primes;
	std::vector<bool> sieve = GenerateSieve(upperBound);
	for (int prime = 2; prime <= upperBound; prime++)
	{
		if (sieve[prime])
		{
			primes.emplace(prime);
		}
	}
	return primes;
}

void CopyPrimesToCout(const std::set<int>& primes)
{
	std::copy(primes.begin(), primes.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}
