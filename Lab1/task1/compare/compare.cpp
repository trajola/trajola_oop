// compare.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

ifstream OpenFileForReading(const string fileName)
{
	ifstream strm(fileName);
	if (!strm.is_open())
	{
		cout << "Failed to open " << fileName << "\n";
	}
	return move(strm);
}

int CompareFiles(const string fileName1, const string fileName2) // 0-equal, 1-different, 2-failed
{
	ifstream file1 = OpenFileForReading(fileName1);
	ifstream file2 = OpenFileForReading(fileName2);
	if (!file1 || !file2)
	{
		return 2;
	}

	string line1, line2;
	int lineIndex;
	for (lineIndex = 1; !file1.eof() && !file2.eof(); lineIndex++)
	{
		getline(file1, line1);
		getline(file2, line2);
		if (line1 != line2)
		{
			cout << "Files are different. Line number is " << lineIndex << ".\n";
			return 1;
		}
	}
	if (!file1.eof() || !file2.eof())
	{		
		cout << "Files are different. Line number is " << lineIndex << ".\n";
		return 1;
	}
	cout << "Files are equal.\n";
	return 0;
}


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid number of arguments.\n";
		cout << "Usage: compare.exe <file1> <file2>\n";
		return 2;
	}

	return  CompareFiles(argv[1], argv[2]);
}

