// Task4_v4_tests.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "../Task4_v4/primes.h"

using namespace std;

bool VectorsAreEqual(vector<bool> const& x, vector<bool> const& y)
{
	return x == y;
}
bool SetsAreEqual(set<int> const& x, set<int> const& y)
{
	return x == y;
}

TEST_CASE("test GetNumber ")
{
	int number;
	CHECK((GetNumber("100", number) && number == 100) == true);
	CHECK((GetNumber("1", number) && number == 1) == true);
	CHECK((GetNumber("100000000", number) && number == 100000000) == true);
	CHECK((GetNumber("100not", number)) == false);
	CHECK((GetNumber("0", number)) == false);
	CHECK((GetNumber("100000001", number)) == false);
	CHECK((GetNumber("10000000000000000", number)) == false);
	CHECK((GetNumber("not a number", number)) == false);
}

TEST_CASE("test GenerateSieve")
{
	using Sieve = std::vector<bool>;
	CHECK(VectorsAreEqual(GenerateSieve(10),
		Sieve{ false, false, true, true, false, true, false, true, false, false, false }));
	CHECK(VectorsAreEqual(GenerateSieve(0), Sieve{ false }));
	CHECK(VectorsAreEqual(GenerateSieve(1), Sieve{ false, false })); 
	CHECK(VectorsAreEqual(GenerateSieve(-1), Sieve{ false }));
}

TEST_CASE("test GeneratePrimeNumbersSet")
{
	CHECK(SetsAreEqual(GeneratePrimeNumbersSet(10), { 2, 3, 5, 7 }));
	CHECK(SetsAreEqual(GeneratePrimeNumbersSet(1), {}));
	CHECK(SetsAreEqual(GeneratePrimeNumbersSet(0), {}));
	CHECK(SetsAreEqual(GeneratePrimeNumbersSet(2), { 2 }));
	CHECK(GeneratePrimeNumbersSet(1000).size() == 168);
}
