// radix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

bool GetNotation(const string & str, int & notation)
{
	size_t stoppedAt;
	notation = 0;
	try
	{
		int number = stoi(str, &stoppedAt);
		if (number < 2 || number > 36)
		{
			return false;
		}
		if (stoppedAt != str.length())
		{
			return false;
		}
		notation = number;
		return true;
	}
	catch (const std::out_of_range)
	{
		return false;
	}
	catch (const std::invalid_argument)
	{
		return false;
	}
}
enum Operation{
	PLUS = 1,
	MINUS = -1,
	MULTY = 0
};

bool CanOverflow(const int & number, const int & some, const Operation & op)
{
	if (op == PLUS && INT_MAX - some < number) 
	{
		return true;
	}

	if (op == MINUS && INT_MIN + some > number)
	{
		return true;
	}

	if (op == MULTY && INT_MAX / some < number)
	{
		return true;
	}

	return false;
}

int StringToInt(const string & str, int radix, bool & wasError) 
{
	const string charDigits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	Operation sign = PLUS;
	auto iStart = str.begin();

	if (str.length() != 0 && str.front() == '-')
	{
		iStart++;
		sign = MINUS;
	}
	
	if (iStart == str.end())
	{
		wasError = true;
		return 0;
	}

	int number = 0, radixPow = 1;
	auto i = str.end();
	do
	{
		i--;
		int digit = charDigits.find_first_of(*i);
		if (digit < 0 || digit >= radix || CanOverflow(number, radixPow * digit, sign))
		{
			wasError = true;
			return 0;
		}
		number += sign * radixPow * digit;
		if (i > iStart)
		{
			if (CanOverflow(radixPow, radix, MULTY))
			{
				wasError = true;
				return 0;
			}
			radixPow *= radix;
		}
	} while (i > iStart);

	wasError = false;
	return number;
}

string IntToString(int value, const int & radix, bool & wasError)
{
	if (value == 0)
	{
		wasError = false;
		return "0";
	}
	if (radix < 2 || radix > 36)
	{
		wasError = true;
		return "";
	}
	const string charDigits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	Operation sign = PLUS;
	if (value < 0)
	{
		sign = MINUS;
	}
	string dstStr("");
	while (value != 0)
	{
		int digit = sign * (value % radix);
		value /= radix;
		if (digit < 0 || digit > 35)
		{
			wasError = true;
			return dstStr;
		}
		dstStr.insert(dstStr.begin(), charDigits.at(digit));
	}
	if (sign == MINUS) 
	{
		dstStr.insert(dstStr.begin(), '-');
	}
	wasError = false;
	return dstStr;
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		cout << "Invalid number of arguments.\n";
		cout << "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	} 
	
	int srcNotation;
	if (!GetNotation(argv[1], srcNotation))
	{
		cout << "Check argument 1.\n";
		cout << "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}

	int dstNotation;
	if (!GetNotation(argv[2], dstNotation))
	{
		cout << "Check argument 2.\n";
		cout << "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}

	bool wasError;
	int srcValue = StringToInt(argv[3], srcNotation, wasError);
	if (wasError)
	{
		cout << "Failed to calc source value.\n";
		cout << "Check your arguments.\n";
		return 1;
	}
	string dstValue = IntToString(srcValue, dstNotation, wasError);
	if (wasError)
	{
		cout << "Something's gone wrong.\n";
		return 1;
	}

//	cout << "src Value = " << srcValue << "\n";
	cout << dstValue << "\n";
	return 0;
}

