// findmax.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "findmax.h"


int main()
{
	std::vector<char *> arr;
	char* maxValue;
	char s1[] = "hello";
	char s2[] = "fox";
	char s3[] = "kittyy";
	arr.push_back(s1);
	arr.push_back(s2);
	arr.push_back(s3);
	FindMax(arr, maxValue);
	return 0;
}

