#include "stdafx.h"
#include "translate.h"

#include <map>
#include <ostream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <string>


Dictionary ReadDictionaryFromStream(std::istream& input)
{
	Dictionary dict;
	std::string line1, line2;
	while (std::getline(input, line1) && std::getline(input, line2))
	{
		dict.emplace(line1, line2);
	}
	return dict;
}

bool ReadDictionaryFromFile(Dictionary& dict, std::string const& fileName)
{
	std::ifstream inFile(fileName);
	if (!inFile.is_open())
		return false;
	dict = ReadDictionaryFromStream(inFile);
	return true;
}

bool WriteDictionaryToStream(Dictionary const& dict, std::ostream& output)
{
	for (const auto & dictPair : dict)
	{
		output << dictPair.first << std::endl << dictPair.second << std::endl;
	}
	return output.good();
}

bool SaveDictionaryToFile(Dictionary const& dict, std::string const& fileName)
{
	std::ofstream outFile(fileName);
	if (!outFile.is_open() || !WriteDictionaryToStream(dict, outFile))
		return false;
	return true;
}

bool Translate(std::string const& inStr, std::string& outStr, Dictionary const& dict)
{
	auto search = dict.find(inStr);
	if (search == dict.end())
	{
		outStr = "";
		return false;
	}
	outStr = search->second;
	return true;
}



