#pragma once

#include <map>
#include <ostream>
#include <istream>

typedef std::map<std::string, std::string> Dictionary;

Dictionary ReadDictionaryFromStream(std::istream& input);

bool SaveDictionaryToFile(std::string const& fileName, Dictionary const& dict);

bool CopyDictionaryToStream(std::ostream out, Dictionary const& dict);

void CopyDictionaryToCout(Dictionary const& Dict);
