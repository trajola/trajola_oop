// Task1_v6.cpp : Defines the entry point for the console application.
//Lab 2, task 1, variant 6
//Умножить каждый элемент массива на максимальный элемент исходного массива
//и разделить на минимальный элемент исходного массива

#include "stdafx.h"
#include "multivector.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>


void PrintArrayToCout(DoubleArray const& numbers)
{
	copy(numbers.begin(), numbers.end(), std::ostream_iterator<double>(std::cout, " "));
	std::cout << std::endl;
}

DoubleArray GetArrayFromCin()
{
	return { std::istream_iterator<double>(std::cin), std::istream_iterator<double>() };
}

void MultToMaxAndDivideToMin(DoubleArray& numbers)
{
	if (numbers.empty())
		return;

	auto minmax = minmax_element(numbers.begin(), numbers.end());
	double transformCoef = fabs(*minmax.first) > 0.1E-10 ? *minmax.second / *minmax.first: *minmax.second;
	transform(numbers.begin(), numbers.end(), numbers.begin(), [&transformCoef](double current) {
		return current * transformCoef;
	});
}

