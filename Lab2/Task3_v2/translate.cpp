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

bool CopyDictionaryToStream(std::ostream out, Dictionary const& dict)
{
	//for (const auto & v : dict)
	{
//		out << v.first << "|" << v.second << std::endl;
	}
	return true;
}

void CopyDictionaryToCout(Dictionary const& dict)
{
	for (const auto & v : dict)
	{
		std::cout << v.first << ", " << v.second << "\n";
	}
}



