// crypt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool GetByte(const string& str, uint8_t& byte)
{
	size_t stoppedAt;
	byte = 0;
	try
	{
		int number = stoi(str, &stoppedAt);
		if (number < 0 || number > UINT8_MAX)
			return false;
		if (stoppedAt != str.length())
			return false;
		byte = static_cast<uint8_t>(number);
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

uint8_t Gamma(const uint8_t& byte, const uint8_t& key) { return byte ^ key; }

uint8_t ShuffleEnc(const uint8_t& byte)
{
	uint8_t bit0 = (byte & (1 << 5)) >> 5;
	uint8_t bit1 = (byte & (1 << 6)) >> 5;
	uint8_t bit2 = (byte & (1 << 0)) << 2;
	uint8_t bit3 = (byte & (1 << 1)) << 2;
	uint8_t bit4 = (byte & (1 << 2)) << 2;
	uint8_t bit5 = (byte & (1 << 7)) >> 2;
	uint8_t bit6 = (byte & (1 << 3)) << 3;
	uint8_t bit7 = (byte & (1 << 4)) << 3;
	return (bit7 | bit6 | bit5 | bit4 | bit3 | bit2 | bit1 | bit0);
}

uint8_t ShuffleDec(const uint8_t& byte)
{
	uint8_t bit0 = (byte & (1 << 2)) >> 2;
	uint8_t bit1 = (byte & (1 << 3)) >> 2;
	uint8_t bit2 = (byte & (1 << 4)) >> 2;
	uint8_t bit3 = (byte & (1 << 6)) >> 3;
	uint8_t bit4 = (byte & (1 << 7)) >> 3;
	uint8_t bit5 = (byte & (1 << 0)) << 5;
	uint8_t bit6 = (byte & (1 << 1)) << 5;
	uint8_t bit7 = (byte & (1 << 5)) << 2;
	return bit7 | bit6 | bit5 | bit4 | bit3 | bit2 | bit1 | bit0;
}

ifstream OpenFileForBinReading(const string& fileName)
{
	ifstream strm(fileName, ios_base::binary);
	if (!strm.is_open())
		cout << "Failed to open " << fileName << "\n";
	return move(strm);
}

ofstream OpenFileForBinWriting(const string& fileName)
{
	ofstream strm(fileName, ios_base::binary);
	if (!strm.is_open())
		cout << "Failed to open " << fileName << "\n";
	return move(strm);
}

bool Encrypt(istream& input, ostream& output, const uint8_t& key)
{
	uint8_t byte;
	while (input.read(reinterpret_cast<char*>(&byte), 1))
	{
		uint8_t byteEnc = Gamma(byte, key);
		byteEnc = ShuffleEnc(byteEnc);
		if (!output.write(reinterpret_cast<char*>(&byteEnc), 1))
		{
			return false;
		}
	}
	return true;
}

bool Decrypt(istream& input, ostream& output, const uint8_t& key)
{
	uint8_t byte;
	while (input.read(reinterpret_cast<char*>(&byte), 1))
	{
		uint8_t byteDec = ShuffleDec(byte);
		byteDec = Gamma(byteDec, key);
		if (!output.write(reinterpret_cast<char*>(&byteDec), 1))
		{
			return false;
		}
	}
	return true;
}
enum ErrorName
{
	INVALID_NUMBER_ARGS = 0,
	INVALID_ARGUMENT = 1
};

struct LaunchErrors
{
	ErrorName name;
	int argNumber;
};

string errorMessage[2] =
{
	"Invalid number of arguments",
	"Check argument "
};

void PrintUsageInstruction()
{
	cout << "Usage for encryption: crypt.exe crypt <input file> <output file> <key 0..255>\n";
	cout << "Usage for decryption: crypt.exe decrypt <input file> <output file> <key 0..255>\n";
}

void PrintErrorLaunchMessage(LaunchErrors error)
{
	cout << errorMessage[error.name];
	if (error.name > 0)
	{
		cout << error.argNumber;
	}
	cout << endl;
	PrintUsageInstruction();
}

bool Cryption(const string & action, const string & inFileName, const string & outFileName,
	const string & keyString)
{
	if (action != "crypt" && action != "decrypt")
	{
		PrintErrorLaunchMessage({ INVALID_ARGUMENT, 1 });
		return false;
	}

	ifstream inFile = OpenFileForBinReading(inFileName);
	if (!inFile)
	{
		PrintErrorLaunchMessage({ INVALID_ARGUMENT, 2 });
		return false;
	}

	ofstream outFile;
	if ((inFileName == outFileName) || !(outFile = OpenFileForBinWriting(outFileName)) || !outFile)
	{
		PrintErrorLaunchMessage({ INVALID_ARGUMENT, 3 });
		return false;
	}

	uint8_t key;
	if (!GetByte(keyString, key))
	{
		PrintErrorLaunchMessage({ INVALID_ARGUMENT, 4 });
		return false;
	}

	if (action == "crypt" && Encrypt(inFile, outFile, key))
	{
		return true;
	}

	if (action == "decrypt" && Decrypt(inFile, outFile, key))
	{
		return true;
	}
	cout << "Something has gone wrong\n";
	return false;
}


int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		PrintErrorLaunchMessage({ INVALID_NUMBER_ARGS, 0 });
		return 1;
	}

	if (!Cryption(argv[1], argv[2], argv[3], argv[4]))
	{
		return 1;
	}
	return 0;
}
