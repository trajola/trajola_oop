#pragma once

#include <map>
#include <ostream>
#include <istream>

typedef std::map<std::string, std::string> Dictionary;

Dictionary ReadDictionaryFromStream(std::istream& input);

bool ReadDictionaryFromFile(Dictionary& dict, std::string const& fileName);

bool WriteDictionaryToStream(Dictionary const& dict, std::ostream& output);

bool SaveDictionaryToFile(Dictionary const& dict, std::string const& fileName);

bool Translate(std::string const& inStr, std::string& outStr, Dictionary const& dict);
