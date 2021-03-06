// copyfile.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Wrong number of arguments.\n";
		cout << "Use copyfile.exe with arguments: copyfile.exe <inputfilename> <outputfilename>\n";
		return 1;
	} 

	//try to open input file
	ifstream inputFile;
	inputFile.open(argv[1]);

	if (!inputFile.is_open())
	{
		cout << "Can't open file " << argv[1] << " for reading.\n";
		return 1;
	}

	//try to open output file
	ofstream outputFile;
	outputFile.open(argv[2]);

	if (!outputFile.is_open())
	{
		cout << "Can't open file " << argv[2] << " for writing.\n";
		return 1;
	}

	char ch;

	while (inputFile.get(ch)) 
	{
		if (!outputFile.put(ch))
		{
			cout << "Can't write to file " << argv[2] << "\n";
			return 1;
		}
	}

	if (!outputFile.flush())
	{
		cout << "Can't save file " << argv[2] << " to disk.\n";
		return 1;
	}

	cout << "File " << argv[1] << " is successfully copied to " << argv[2] << ".\n";
	
	return 0;
}

