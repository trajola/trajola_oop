// Task1_v6.cpp : Defines the entry point for the console application.
//Умножить каждый элемент массива на максимальный элемент исходного массива 
//и разделить на минимальный элемент исходного массива

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>

using namespace std;
typedef vector<double> DoubleArray;

void PrintArrayToCout(const DoubleArray & numbers)
{
	copy(numbers.begin(), numbers.end(), ostream_iterator<double>(cout, " "));
	cout << endl;
}

void GetArrayFromCin(DoubleArray & numbers)
{
	string str;
	getline(cin, str);
	istringstream lineWithDoubles;
	lineWithDoubles.str(str);
	copy(istream_iterator<double>(lineWithDoubles), istream_iterator<double>(), back_inserter(numbers));
}

void MultiToMaxAndDivideToMin(DoubleArray & numbers)
{
	double minNumber = * min_element(numbers.begin(), numbers.end());
	double maxNumber = * max_element(numbers.begin(), numbers.end());

	transform(numbers.begin(), numbers.end(), numbers.begin(), [&maxNumber](double current) {
		return current * maxNumber;
	});

	if (fabs(minNumber) > 0.1E-10)
	{
		transform(numbers.begin(), numbers.end(), numbers.begin(), [&minNumber](double current) {
			return current / minNumber;
		});
	}
}

int main()
{
	DoubleArray numbers;
	GetArrayFromCin(numbers);
	MultiToMaxAndDivideToMin(numbers);
	PrintArrayToCout(numbers);

	return 0;
}

