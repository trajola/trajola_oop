#pragma once

#include <map>
#include <ostream>
#include <istream>

enum  class Action
{
	START,
	WAIT_WORD,
	ANKNOWN_WORD,
	STOP_AND_EXIT
};

struct State
{
	bool dictChanged;
	Action toDo;
};

typedef std::map<std::string, std::string> Dictionary;

Dictionary ReadDictionaryFromStream(std::istream& input);

bool SaveDictionaryToFile(std::string const& fileName, Dictionary const& dict);

bool WriteDictionaryToStream(Dictionary const& dict, std::ostream& output);

void CopyDictionaryToCout(Dictionary const& Dict);
