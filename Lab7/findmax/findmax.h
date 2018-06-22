#pragma once
#include <vector>
#include <iostream>
#include <functional>

template < typename T >
bool FindMax(std::vector<T> const & arr, T & maxValue)
{
	if (arr.empty())
		return false;

	auto max = arr.cbegin();
	for (auto i = arr.cbegin(); i != arr.cend(); i++)
		if (*max < *i)
			max = i;

	maxValue = *max;
	return true;
}

template <>
bool FindMax<const char*>(std::vector<const char*> const & arr, const char * & maxValue)
{
	if (arr.empty())
		return false;

	auto max = arr.begin();
	for (auto i = arr.cbegin(); i != arr.cend(); i++)
		if (strcmp(*i, *max) > 0)
			max = i;

	maxValue = *max;
	return true;
}

template < typename T, typename Less >
bool FindMaxEx(std::vector<T> const & arr, T & maxValue, Less const& less)
{
	if (arr.empty())
		return false;

	auto max = arr.begin();
	for (auto i = arr.cbegin(); i != arr.cend(); i++)
		if (less(*max , *i))
			max = i;

	maxValue = *max;
	return true;
}
