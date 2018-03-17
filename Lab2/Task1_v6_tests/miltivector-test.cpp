#include "stdafx.h"
#include "../Task1_v6/multivector.h"

using namespace std;

bool VectorsAreEqual(DoubleArray const& x, DoubleArray const& y)
{
	return x == y;
}

TEST_CASE("vector_common_correct_transform")
{
	DoubleArray numbersCheck = { 2, -1, 4.5 };
	MultToMaxAndDivideToMin(numbersCheck);
	CHECK(VectorsAreEqual(numbersCheck, { -9, 4.5, -20.25 }));
}
TEST_CASE("vector_all_1_correct_transform")
{
	DoubleArray numbersCheck = { 1, 1, 1 };
	MultToMaxAndDivideToMin(numbersCheck);
	CHECK(VectorsAreEqual(numbersCheck, { 1, 1, 1 }));
}
TEST_CASE("vector_1_number")
{
	DoubleArray numbersCheck = { -5 };
	MultToMaxAndDivideToMin(numbersCheck);
	CHECK(VectorsAreEqual(numbersCheck, { -5 }));
}

TEST_CASE("not_divide_to_0_vector")
{
	DoubleArray numbersCheck = { 1, 0, 4.5 };
	MultToMaxAndDivideToMin(numbersCheck);
	CHECK(VectorsAreEqual(numbersCheck, { 4.5, 0, 20.25 }));
}
TEST_CASE("not_divide_to_0_only0")
{
	DoubleArray numbersCheck = { 0 };
	MultToMaxAndDivideToMin(numbersCheck);
	CHECK(VectorsAreEqual(numbersCheck, { 0 }));
}

TEST_CASE("empty_vector_transform_to_empty_vector")
{
	DoubleArray emptyVector;
	MultToMaxAndDivideToMin(emptyVector);
	CHECK(emptyVector.empty());
}

	

