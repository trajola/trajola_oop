#pragma once
#include <vector>

typedef std::vector<double> EquationRoot;

EquationRoot Solve4(double a, double b, double c, double d, double e);
EquationRoot Solve3(double a, double b, double c, double d);
EquationRoot Solve2(double a, double b, double c);