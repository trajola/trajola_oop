// calcbits.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

enum ConvertResult
{
	SUCCESS,
	OUT_OF_BOUNDS,
	FAILED
};

ConvertResult GetByte(const string & str, uint8_t & byte)
{
	size_t stoppedAt;
	byte = 0;
	try
	{
		int number = stoi(str, &stoppedAt);
		if (number < 0 || number > UINT8_MAX)
		{
			return OUT_OF_BOUNDS;
		}
		if (stoppedAt != str.length())
		{
			return FAILED;
		}
		byte = static_cast<uint8_t>(number);
		return SUCCESS;
	}
	catch (const std::out_of_range)
	{
		return FAILED;
	} 
	catch (const std::invalid_argument)
	{
		return FAILED;
	}

}

int Calc1Bits(const uint8_t byte)
{
	int count1Bits = 0;
	for (int pos = 0; pos < 8; pos++)
	{
		if (byte & (1 << pos))
		{
			count1Bits += 1;
		}
	}
	return count1Bits;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid number of arguments.\n";
		cout << "Usage: calcbits.exe <byte 0..255>\n";
		return 1;
	}
	
	uint8_t byte;
	ConvertResult getByteResult = GetByte(argv[1], byte);
	switch (getByteResult)
	{
	case FAILED:
		cout << "Failed to convert '" << argv[1] << "' to number.\n";
		return 1;
	case OUT_OF_BOUNDS:
		cout << "Failed, the number '" << argv[1] << "' is out of bounds 0..255.\n";
		return 1;
	default:
		cout << Calc1Bits(byte) << " bits = 1.\n";
		return 0;
	}
}

