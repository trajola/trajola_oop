// invert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>

using namespace std;
typedef double Matrix3x3[3][3];

void PrintMatrix3x3(Matrix3x3 mat)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << setw(8) << right << fixed << setprecision(3) << mat[i][j];
		}
		cout << "\n";
	}
}

int main()
{
	Matrix3x3 matA = {
		{2, 5, 7},
		{6, 3, 4},
		{5, -2, -3}
	};
	PrintMatrix3x3(matA);
	
	
	
	return 0;
}

