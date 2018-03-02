// crypt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool GetByte(const string & str, uint8_t & byte)
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

uint8_t Gamma(const uint8_t & byte, const uint8_t & key)
{
	return byte ^ key;
}

uint8_t ShuffleEnc(const uint8_t & byte)
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

uint8_t ShuffleDec(const uint8_t & byte)
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

ifstream OpenFileForBinReading(const string & fileName)
{
	ifstream strm(fileName, ios_base::binary);
	if (!strm.is_open())
		cout << "Failed to open " << fileName << "\n";
	return move(strm);
}

ofstream OpenFileForBinWriting(const string & fileName)
{
	ofstream strm(fileName, ios_base::binary);
	if (!strm.is_open())
		cout << "Failed to open " << fileName << "\n";
	return move(strm);
}

void Encrypt(istream & input, ostream& output, const uint8_t & key)
{
	uint8_t byte;
	while (input.read(reinterpret_cast<char*>(&byte), 1))
	{
	uint8_t byteEnc = Gamma(byte, key);
	byteEnc = ShuffleEnc(byteEnc);
	output.write(reinterpret_cast<char*>(&byteEnc), 1);
	} 
}

void Decrypt(istream & input, ostream& output, const uint8_t & key)
{
	uint8_t byte;
	while (input.read(reinterpret_cast<char*>(&byte), 1))
	{
		uint8_t byteDec = ShuffleDec(byte);
		byteDec = Gamma(byteDec, key);
		output.write(reinterpret_cast<char*>(&byteDec), 1);
	}
}


int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		cout << "Invalid number of arguments.\n";
		cout << "Usage for encryption: crypt.exe crypt <input file> <output file> <key 0..255>\n";
		cout << "Usage for decryption: crypt.exe decrypt <input file> <output file> <key 0..255>\n";
		return 1;
	}

	string action = argv[1];
	if (action != "crypt" && action != "decrypt")
	{
		cout << argv[1] << " Check argument 1.\n";
		cout << "Usage for encryption: crypt.exe crypt <input file> <output file> <key 0..255>\n";
		cout << "Usage for decryption: crypt.exe decrypt <input file> <output file> <key 0..255>\n";
		return 1;
	}
	
	uint8_t key;
	if (!GetByte(argv[4], key))
	{
		cout << "Check argument 4.\n";
		cout << "Usage for encryption: crypt.exe crypt <input file> <output file> <key 0..255>\n";
		cout << "Usage for decryption: crypt.exe decrypt <input file> <output file> <key 0..255>\n";
		return 1;
	}
	
	ifstream inFile = OpenFileForBinReading(argv[2]);
	ofstream outFile = OpenFileForBinWriting(argv[3]);

	if (!inFile || !outFile) 
	{
		cout << "Check input and output files.\n";
		return 1;
	}
	if (action == "crypt")
	{
		Encrypt(inFile, outFile, key);
	}

	if (action == "decrypt")
	{
		Decrypt(inFile, outFile, key);
	}
	return 0;
}

