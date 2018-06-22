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
		AddWord(line1, line2, dict);
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

void Translate(std::string const& inStr, std::string& outStr, Dictionary const& dict)
{
	auto range = dict.equal_range(inStr);
	outStr = "";
	for (auto t = range.first; t != range.second; ++t)
		(outStr == "") ? outStr.append(t->second) : outStr.append(", " + t->second);
}

bool PairExists(std::string const& inStr, std::string const& translatedStr, Dictionary const& dict)
{
	auto range = dict.equal_range(inStr);
	bool exist = false;
	for (auto t = range.first; t != range.second; ++t)
		if (t->second == translatedStr)
			return true;
	return exist;
}

void AddWord(std::string const& inStr, std::string const& translatedStr, Dictionary & dict)
{
	if (!PairExists(inStr, translatedStr, dict))
		dict.emplace(inStr, translatedStr);
	if (!PairExists(translatedStr, inStr, dict))
		dict.emplace(translatedStr, inStr);
}



