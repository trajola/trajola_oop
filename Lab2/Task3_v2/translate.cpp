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
	return outFile.is_open() && WriteDictionaryToStream(dict, outFile);
}

void Translate(std::string const& srcStr, std::string& dstStr, Dictionary const& dict)
{
	auto range = dict.equal_range(srcStr);
	dstStr = "";
	for (auto t = range.first; t != range.second; ++t)
		(dstStr == "") ? dstStr.append(t->second) : dstStr.append(", " + t->second);
}

bool TranslationExists(std::string const& srcStr, std::string const& dstStr, Dictionary const& dict)
{
	auto range = dict.equal_range(srcStr);
	return std::find_if(range.first, range.second, [&dstStr](auto&& t) {
		return t.second == dstStr; 
	}) != range.second;
}

void AddWord(std::string const& srcStr, std::string const& dstStr, Dictionary & dict)
{
	if (!TranslationExists(srcStr, dstStr, dict))
		dict.emplace(srcStr, dstStr);
	if (!TranslationExists(dstStr, srcStr, dict))
		dict.emplace(dstStr, srcStr);
}



