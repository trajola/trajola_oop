#include "stdafx.h"
#include "translate.h"

#include <map>
#include <ostream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <string>



bool SaveDictionaryToFile(std::string const& fileName, Dictionary const& dict) 
{
	return true;
}

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

bool WriteDictionaryToStream(Dictionary const& dict, std::ostream& output)
{
	for (const auto & dictPair : dict)
	{
		output << dictPair.first << std::endl << dictPair.second << std::endl;
	}
	return output.good();
}




