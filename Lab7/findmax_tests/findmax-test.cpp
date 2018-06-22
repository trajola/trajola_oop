#include "stdafx.h"
#include "../findmax/findmax.h"
#include <vector>
#include <string>

TEST_CASE("Find max in integer array")
{
	std::vector<int> arr;
	int maxValue;
	CHECK(!FindMax(arr, maxValue));
	arr = { 1, -5, 3, 8, 6 };
	CHECK((FindMax(arr, maxValue) && maxValue == 8) == true);
}

TEST_CASE("Find max in real array")
{
	std::vector<double> arr;
	double maxValue;
	CHECK(!FindMax(arr, maxValue));
	arr = { 1.0, -5.5, 8.9, 9.1 };
	CHECK((FindMax(arr, maxValue) && maxValue == 9.1) == true);
}

TEST_CASE("Find max in strings array")
{
	std::vector<std::string> arr;
	std::string maxValue;
	CHECK(!FindMax(arr, maxValue));
	arr = { "array", "fox", "kitty", "dog" };
	CHECK((FindMax(arr, maxValue) && maxValue == "kitty") == true);
}

TEST_CASE("Find max in char* strings array")
{
	std::vector<char *> arr;
	char* maxValue;
	CHECK(!FindMax(arr, maxValue));
	char s1[] = "hello";
	char s2[] = "fox";
	char s3[] = "kittyy";
	arr.push_back(s1);
	arr.push_back(s2);
	arr.push_back(s3);
	FindMax(arr, maxValue);
	//CHECK(maxValue == "fox");
}

struct Athlete 
{
	std::string name;
	double height, weight;
};

std::vector<Athlete> athletes = {
	{"One", 178, 78},
	{"Two", 200, 89},
	{"Tree", 189, 95}
};

bool LessWeight(Athlete const & a1, Athlete const & a2)
{
	return (a1.weight < a2.weight);
}

bool LessHeight(Athlete const & a1, Athlete const & a2)
{
	return (a1.height < a2.height);
}


TEST_CASE("Return false for empty arr")
{
	Athlete max;
	std::vector<Athlete> emptyArr;
	CHECK(FindMaxEx(emptyArr, max, LessWeight) == false);
}

TEST_CASE("Find max height athlete")
{
	Athlete max;
	CHECK(FindMaxEx(athletes, max, 
		[](Athlete const & a1, Athlete const & a2) {
		return (a1.height < a2.height);
	}));
	CHECK(max.height == 200);
	CHECK(max.name == "Two");
}

TEST_CASE("Find max weight athlete")
{
	Athlete max;
	CHECK(FindMaxEx(athletes, max, 
		[](Athlete const & a1, Athlete const & a2) {
		return (a1.weight < a2.weight);
	}));
	CHECK(max.weight == 95);
	CHECK(max.name == "Tree");
}
 