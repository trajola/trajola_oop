// rotatebyte.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

bool GetNumberFromStr(string str, unsigned char* number, int minBound, int maxBound )
{

	int tmpNumber;
	size_t stoppedAt;
	*number = 0;
	try
	{
		stoi(str);
		/*	if (stoppedAt != str.length())
		{
			cout << "Failed convert " << str << " to number at pos " << stoppedAt << ".\n";
			return false;
		}
		if (tmpNumber < minBound || tmpNumber > maxBound)
		{
			cout << "Failed, the number is out of bounds "<< minBound << ".." << maxBound<< ". \n";
			return false;
		} */
	}
	catch (const std::out_of_range & err)
	{
		cout << "Failed convert " << str << " to number at pos 1.\n";
		return false;
	}
//	*number = tmpNumber;
	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Invalid number of arguments.\n";
		cout << "Usage: rotatebyte.exe <byte 0..255> <number of bits 1..7> <L / R> \n";
		return 1;
	}
	
	unsigned char byte;
	if (!GetNumberFromStr(argv[1], &byte, 0, 255))
	{
		cout << "Check argument 1.\n";
		return 1;
	}

	unsigned char shift;
	if (!GetNumberFromStr(argv[2], &shift, 1, 7))
	{
		cout << "Check argument 2.\n";
		return 1;
	}

	string direction = argv[3];
	if (direction != "L" && direction != "R")
	{
		cout << "Got " << argv[3] <<" instead of L / R.\nCheck argument 3.\n";
		return 1;
	}

	//unsigned short tmp1 = byte, tmp2 = shift;
	//cout << "Shift byte " << tmp1 << " " << direction << " to " << tmp2 << " bits.\n";
	return 0;
}


