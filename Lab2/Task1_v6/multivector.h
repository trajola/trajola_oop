#pragma once
#include <vector>

typedef std::vector<double> DoubleArray;

void PrintArrayToCout(DoubleArray const& numbers);

DoubleArray GetArrayFromCin();

void MultToMaxAndDivideToMin(DoubleArray& numbers);
