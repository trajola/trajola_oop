#include "stdafx.h"
#include "solve.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

int sign(double x)
{
	if (x > 0)
		return 1;
	if (x < 0)
		return -1;
	return 0;
}

EquationRoot Solve4(double a, double b, double c, double d, double e)
{
	if (a == 0)
		throw std::invalid_argument("Coefficient a = 0 is not allowed");

	double a0 = a;
	a = b / a0;
	b = c / a0;
	c = d / a0;
	d = e / a0;

	EquationRoot solution3 = Solve3(1, -b, a * c - 4 * d, -pow(a, 2) * d + 4 * b * d - pow(c, 2));
	double y0 = solution3[solution3.size()- 1];
	double r = sqrt(pow(a, 2) / 4.0 - b + y0);
	double q = (a / 2.0 * y0 - c) < 0 ? -sqrt(pow(y0, 2) / 4.0 - d) : sqrt(pow(y0, 2) / 4.0 - d);

	EquationRoot solution21 = Solve2(1, a / 2.0 + r, y0 / 2.0 + q);
	EquationRoot solution22 = Solve2(1, a / 2.0 - r, y0 / 2.0 - q);

	EquationRoot solution;
	std::set_union(solution21.begin(), solution21.end(), solution22.begin(), solution22.end(), std::back_inserter(solution));

	if (solution.empty())
		throw std::domain_error("There are no rational roots");
	
	std::sort(solution.begin(), solution.end());
	return solution;
} 

EquationRoot Solve3(double a, double b, double c, double d)
{
	double a0 = a;
	a = b / a0;
	b = c / a0;
	c = d / a0;

	double r = (2 * pow(a, 3) - 9 * a * b + 27 * c) / 54;
	double q = (pow(a, 2) - 3 * b) / 9;
	double s = (pow(q, 3) - pow(r, 2));

	EquationRoot solution;
	if (s > 0)
	{
		double f = 1.0 / 3 * acos(r / sqrt(pow(q, 3)));
		solution.push_back(-2 * sqrt(q) * cos(f) - a / 3);
		solution.push_back(-2 * sqrt(q) * cos(f + 2.0 / 3 * M_PI) - a / 3);
		solution.push_back(-2 * sqrt(q) * cos(f - 2.0 / 3 * M_PI) - a / 3);
	}
	if (s < 0) 
	{
		if (q > 0)
			solution.push_back(-2 * sign(r) * sqrt(q) * cosh(acosh(abs(r) / sqrt(pow(q, 3))) / 3) - a / 3);
		if (q < 0)
			solution.push_back(-2 * sign(r) * sqrt(abs(q)) * sinh(asinh(abs(r) / sqrt(pow(abs(q), 3))) / 3) - a / 3);
		if (q == 0)
		{
			double p = sign((c - pow(a, 3) / 27)) * pow(abs((c - pow(a, 3) / 27)), 1.0 / 3.0);
			solution.push_back(-p - a / 3);
		}
	} 
	if (s == 0)
	{
		solution.push_back(-2 * sign(r) * sqrt(q) - a / 3);
		solution.push_back(sign(r) * sqrt(q) - a / 3);
	}
	std::sort(solution.begin(), solution.end());
	return solution;
}

EquationRoot Solve2(double a, double b, double c)
{
	EquationRoot solution;
	double d = pow(b, 2) - 4 * a* c;
	if (d > 0)
	{
		solution.push_back((-b + sqrt(d)) / (2 * a));
		solution.push_back((-b - sqrt(d)) / (2 * a));
	}
	if (d == 0)
		solution.push_back(-b / (2 * a));

	std::sort(solution.begin(), solution.end());
	return solution;
}