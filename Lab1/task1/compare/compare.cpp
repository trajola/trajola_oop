// compare.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

ifstream OpenFileForReading(const string & fileName)
{
	ifstream strm(fileName);
	if (!strm.is_open())
	{
		cout << "Failed to open " << fileName << "\n";
	}
	return move(strm);
}

enum CompareResult
{
	EQUAL,
	DIFFERENT,
	FAILED
};

CompareResult CompareStreams(istream& stream1, istream& stream2, int & lineIndex)
{
	if (!stream1 || !stream2)
	{
		return FAILED;
	}

	string line1, line2;
	for (lineIndex = 1; !stream1.eof() && !stream2.eof(); lineIndex++)
	{
		getline(stream1, line1);
		getline(stream2, line2);
		if (line1 != line2)
		{
			return DIFFERENT;
		}
	}
	if (!stream1.eof() || !stream2.eof())
	{
		return DIFFERENT;
	}
	return EQUAL;
}

int CompareFiles(const string & fileName1, const string & fileName2)
{
	ifstream file1 = OpenFileForReading(fileName1);
	ifstream file2 = OpenFileForReading(fileName2);
	int errorLineIndex = 0;
	CompareResult compareFilesResult = CompareStreams(file1, file2, errorLineIndex);
	switch (compareFilesResult)
	{
		case EQUAL: 
			cout << "Files are equal.\n";
			return 0;
		case DIFFERENT:
			cout << "Files are different. Line number is " << errorLineIndex << ".\n";
			return 1;
		default:
			cout << "Comparing failed.\n";
			return 2;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid number of arguments.\n";
		cout << "Usage: compare.exe <file1> <file2>\n";
		return 2;
	}

	return CompareFiles(argv[1], argv[2]);

}

