// calcbits.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

int GetByte(string str, uint8_t* byte)
{
	unsigned char tmpNumber;
	size_t stoppedAt;
	*byte = 0;
	try
	{
		int number = stoi(str, &stoppedAt);
		if (number<0 || number > UINT8_MAX)
		{
			*byte = static_cast<uint8_t>(number);
			return 0;
		}
		if (stoppedAt != str.length())
		{
			return stoppedAt + 1;
		}
	/*	if (str.length() > 3 || tmpNumber > 255)
		{
			return -1;
		}*/
	}
	catch (const std::out_of_range & err)
	{
		return 1;
	} 

	*byte = tmpNumber;
	return 0;
}

int Calc1Bits(const char byte)
{
	int number1Bits = 0;
	for (int pos = 0; pos < 8; pos++)
	{
		if (byte & (1 << pos))
		{
			number1Bits += 1;
		}
	}
	return number1Bits;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid number of arguments.\n";
		cout << "Usage: calcbits.exe <byte 0..255>\n";
		return 1;
	}
	
	unsigned char byte;
	int posConvertError = GetByte(argv[1], &byte);
	if (posConvertError)
	{
		if (posConvertError < 0)
		{
			cout << "Failed, the number is too big. \n";
		}
		else
		{
			cout << "Failed convert " << argv[1] << " to byte at pos " << posConvertError << ".\n";
		}
		cout << "Usage: calcbits.exe <byte 0..255>\n";
		return 1;
	}
	unsigned short y = byte;
	cout << "In byte " << y << ", " << Calc1Bits(byte) << " bits=1.\n";

//	cout << Calc1Bits(byte) << "\n";
	return 0;
}

