#pragma once

#include <string>
#include <set>
#include <vector>


const size_t upperBoundMax = 100000000;

bool GetNumber(std::string const& str, int& number);

std::vector<bool> GenerateSieve(int upperBound);

std::set<int> GeneratePrimeNumbersSet(int upperBound);

void CopyPrimesToCout(const std::set<int>& primes);
