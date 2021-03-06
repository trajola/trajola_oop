// rotatebyte.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

enum ConvertResult
{
	SUCCESS = true,
	OUT_OF_BOUNDS = false,
	FAILED = false
};

ConvertResult GetByte(const string & str, uint8_t & byte, const uint8_t & min_bound, const uint8_t & max_bound)
{
	size_t stoppedAt;
	byte = 0;
	try
	{
		int number = stoi(str, &stoppedAt);
		if (number < min_bound || number > max_bound)
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

uint8_t rotateByte1L(const uint8_t & byte)
{
	uint8_t bitLeft = byte & (1 << 7);
	return (byte << 1) | (bitLeft >> 7);
}

uint8_t rotateByte1R(const uint8_t & byte)
{
	uint8_t bitRight = byte & 1;
	return (byte >> 1) | (bitRight << 7);
}

uint8_t rotateByte1D(const uint8_t & byte, const string direction)
{
	if (direction == "L")
	{
		return rotateByte1L(byte);
	}
	if (direction == "R")
	{
		return rotateByte1R(byte);
	}
		return 0;
}

uint8_t rotateByte(const uint8_t & byte, const uint8_t shift, const string direction)
{
	uint8_t resultByte = byte;
	for (int i = 0; i < shift; ++i)
	{
		resultByte = rotateByte1D(resultByte, direction);
	}
	return resultByte;
}


int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Invalid number of arguments.\n";
		cout << "Usage: rotatebyte.exe <byte 0..255> <number of bits 1..7> <L / R>\n";
		return 1;
	}
	
	uint8_t byte;
	if (!GetByte(argv[1], byte, 0, 255))
	{
		cout << "Check argument 1.\n";
		cout << "Usage: rotatebyte.exe <byte 0..255> <number of bits 1..7> <L / R>\n";
		return 1;
	}

	uint8_t shift;
	if (!GetByte(argv[2], shift, 1, 7))
	{
		cout << "Check argument 2.\n";
		cout << "Usage: rotatebyte.exe <byte 0..255> <number of bits 1..7> <L / R>\n";
		return 1;
	}

	string direction = argv[3];
	if (direction != "L" && direction != "R" && direction != "r" && direction != "l")
	{
		cout << "Got '" << argv[3] << "' instead of L / R.\n";
		cout << "Check argument 3.\n";
		cout << "Usage: rotatebyte.exe <byte 0..255> <number of bits 1..7> <L / R>\n";
		return 1;
	}

	int resultNumber = rotateByte(byte, shift, direction);
	cout << resultNumber << "\n";
	return 0;
}


