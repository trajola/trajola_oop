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
			cout << setw(8) << right << fixed << setprecision(3) << mat[i][j];
		cout << "\n";
	}
}

double Calculate1Minor3x3(Matrix3x3 mat, const int & row, const int & col)
{
	double mat2x2[2][2];
	int i2 = 0, j2 = 0;
	for (int i = 0; i < 3; i++)
	{
		j2 = 0;
		if (i != row)
		{
			for (int j = 0; j < 3; j++)
				if (j != col)
					mat2x2[i2][j2++] = mat[i][j];
			i2++;
		}	
	}
	return mat2x2[0][0] * mat2x2[1][1] - mat2x2[0][1] * mat2x2[1][0];
}

double CalculateDeterminant3x3(Matrix3x3 mat)
{
	double  det = 0; 
	//by 0 row
	det += mat[0][0] * Calculate1Minor3x3(mat, 0, 0);
	det -= mat[0][1] * Calculate1Minor3x3(mat, 0, 1);
	det += mat[0][2] * Calculate1Minor3x3(mat, 0, 2);
	return det;
}

void TransposeMatrix3x3(Matrix3x3 src, Matrix3x3 dst)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			dst[i][j] = src[j][i];
}

bool InvertMatrix(Matrix3x3 mat, Matrix3x3 matI)
{
	double determinant = CalculateDeterminant3x3(mat);
	if (fabs(determinant) < 0.1E-10)
		return false;

	Matrix3x3 minor;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			minor[i][j] = Calculate1Minor3x3(mat, i, j);
			if ((i + j) % 2)
				minor[i][j] *= -1;
			minor[i][j] = minor[i][j] * determinant;
		}	
	TransposeMatrix3x3(minor, matI);
	return true;
}


int main()
{
	Matrix3x3 matA = {
		{2, 5, 7},
		{6, 3, 4},
		{5, -2, -3}
	};
	PrintMatrix3x3(matA);

	Matrix3x3 matAI;
	
	if (!InvertMatrix(matA, matAI))
	{
		cout << "Determinant = 0. Inverse matrix doesn't exist.\n";
		return 0;
	}

	cout << "Inverted matrix:\n";
	PrintMatrix3x3(matAI);
	
	return 0;
}

