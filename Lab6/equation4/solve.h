#pragma once
#include <vector>

struct EquationRoot
{
	int numRoots = 0;
	std::vector<double> roots;
};


EquationRoot Solve4(double a, double b, double c, double d, double e);
EquationRoot Solve3(double a, double b, double c, double d);
EquationRoot Solve2(double a, double b, double c);