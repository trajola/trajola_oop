// Task3_v2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "translate.h"

#include <iostream>
#include <string>

enum StateType
{
	EXIT,
	TRANSLATE,
	ADD_TO_DICTIONARY,
};

void HandleTranslate(StateType& state, std::string & readStrPrev, std::string const& readStr, Dictionary& dict, bool& dictChanged)
{
	std::string translatedStr;
	Translate(readStr, translatedStr, dict);
	if (translatedStr != "")
		std::cout << translatedStr << "\n";
	else
	{
		state = ADD_TO_DICTIONARY;
		readStrPrev = readStr;
		std::cout << "Don't know. Enter translation or empty enter to reject.\n";
	}
	return;
}

void HandleAddToDictionary(StateType& state, std::string & readStrPrev, std::string const& readStr, Dictionary& dict, bool& dictChanged)
{
	if (readStr != "")
	{
		AddWord(readStrPrev, readStr, dict);
		dictChanged = true;
		std::cout << "The word \"" << readStrPrev << "\" and its translation \"" << readStr << "\" is added.\n";
	}
	else
		std::cout << "The word \"" << readStrPrev << "\" is ignored.\n";

	state = TRANSLATE;
	return;
}

void ProcessTranslation(Dictionary & dict, bool& dictChanged)
{
	StateType state = TRANSLATE;
	std::string readStr, readStrPrev;
	while (state != EXIT)
	{
		std::cout << ">";
		if (!std::getline(std::cin, readStr) || (readStr == "..."))
			state = EXIT;
		else
		{ 
			if (state == TRANSLATE)
				HandleTranslate(state, readStrPrev, readStr, dict, dictChanged);
			else if (state == ADD_TO_DICTIONARY)
				HandleAddToDictionary(state, readStrPrev, readStr, dict, dictChanged);
		}
	}
}

void HandleDictSaving(Dictionary & dict, std::string const & dictFileName)
{
	std::cout << "The dictionary has been changed. Enter \"Y\" or \"y\" to save.\n";
	std::string action;
	if (std::getline(std::cin, action) && (action == "Y" || action == "y"))
	{
		SaveDictionaryToFile(dict, dictFileName);
		std::cout << "Changes to dictionary are saved, exiting.\n";
	}
	else
		std::cout << "Changes to dictionary are not saved, exiting.\n";
}

int main(int argc, char* argv[])
{
	Dictionary dict;
	std::string dictFileName = "dict.txt";
	if (argc == 2)
	{
		dictFileName = argv[1];
	}
	else
		std::cout << "Default dictionary name is " << dictFileName << "\n";
	ReadDictionaryFromFile(dict, dictFileName);
	bool dictChanged = false;

	std::cout << "Hi! Enter words to translate. \n";
	ProcessTranslation(dict, dictChanged);

	if (dictChanged)
		HandleDictSaving(dict, dictFileName);

	std::cout << "GoodBye.\n";
	return 0;
}
