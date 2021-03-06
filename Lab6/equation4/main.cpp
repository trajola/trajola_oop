// equation4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "solve.h"
#include <iostream>
#include <iterator>

bool GetCoefficients(std::istream & inStrm, double &a, double &b, double &c, double &d, double &e)
{
	return (inStrm >> a) && (inStrm >> b) && (inStrm >> c) && (inStrm >> d) && (inStrm >> e);
}

int main()
{
	double a, b, c, d, e;
	while (GetCoefficients(std::cin, a, b, c, d, e))
	{
		try
		{
			EquationRoot solution = Solve4(a, b, c, d, e);
			std::copy(solution.roots.begin(), solution.roots.end(), std::ostream_iterator<double>(std::cout, " "));
			std::cout << std::endl;
		}
		catch (const std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return 0;
}

