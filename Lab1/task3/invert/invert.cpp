// invert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;
typedef double Matrix3x3[3][3];

void PrintMatrix3x3(Matrix3x3 mat)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cout << setw(15) << right << fixed << setprecision(3) << mat[i][j];
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
			minor[i][j] = minor[i][j] / determinant;
		}	
	TransposeMatrix3x3(minor, matI);
	return true;
}


ifstream OpenFileForReading(const string & fileName)
{
	ifstream strm(fileName);
	if (!strm.is_open())
	{
		cout << "Failed to open " << fileName << "\n";
	}
	return move(strm);
}

bool GetMatrix3x3FromFile(Matrix3x3 mat, const string & fileName)
{
	ifstream inFile = OpenFileForReading(fileName);
	if (!inFile) 
		return false;
	
	for (int i = 0; i < 3; i++)
	{
		string str;
		if (!getline(inFile, str))
			return false;
		istringstream row;
		row.str (str);
		for (int j = 0; j < 3; j++)
			row >> mat[i][j];
	}
	return true;
}

void MultiMatrix3x3(Matrix3x3 m1, Matrix3x3 m2, Matrix3x3 resultMatrix)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			resultMatrix[i][j] = 0;
			for (int k = 0; k < 3; k++)
				resultMatrix[i][j] += m1[i][k] * m2[k][j];
		}
}


int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "Invalid number of arguments.\n";
		cout << "Usage: invert.exe <matrix file>\n";
		return 1;
	}
	
	Matrix3x3 matA;
	if (!GetMatrix3x3FromFile(matA, argv[1]))
	{
		cout << "Something's gone wrong while reading matrix.\n";
		return 1;
	}
	cout << "Initial matrix:\n";
	PrintMatrix3x3(matA);

	Matrix3x3 matAI;	
	if (!InvertMatrix(matA, matAI))
	{
		cout << "Determinant = 0. Inverse matrix doesn't exist.\n";
		return 0;
	}

	cout << "Inverted matrix:\n";
	PrintMatrix3x3(matAI);

	Matrix3x3 c;
	MultiMatrix3x3(matA, matAI, c);
	cout << "A * AI = \n";
	PrintMatrix3x3(c);

	return 0;
}

