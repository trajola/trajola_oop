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
	ADD_WORD_TO_DICTIONARY,
	SAVE_DICTIONARY
};


void HandleAction(StateType& state, std::string & inStrPrev, std::string const& inStr, Dictionary& dict, bool& dictChanged)
{
	if (inStr == "...")
	{
		if (dictChanged)
		{
			state = SAVE_DICTIONARY;
		}		
		else
			state = EXIT;
		return;
	}

	if (state == TRANSLATE)
	{
		std::string translation;
		Translate(inStr, translation, dict);
		if (translation != "")
			std::cout << translation << "\n";
		else
		{
			state = ADD_WORD_TO_DICTIONARY;
			inStrPrev = inStr;
			std::cout << "Don't know. Enter translation or empty enter to reject.\n";
		}
		return;
	}

	if (state == ADD_WORD_TO_DICTIONARY)
	{
		if (inStr != "")
		{
			AddWord(inStrPrev, inStr, dict);
			dictChanged = true;
			std::cout << "The word \"" << inStrPrev << "\" and its translation \""<< inStr << "\" is added.\n";
		}
		else
		{
			std::cout << "The word \"" << inStrPrev << "\" is ignored.\n";
		}
		state = TRANSLATE;
		return;
	}
}

int main(int argc, char* argv[])
{
	Dictionary dict;
	ReadDictionaryFromFile(dict, argv[1]);
	bool dictChanged = false;
	StateType state = TRANSLATE;
	std::string inStr, inStrPrev;
	std::cout << "Hi! Enter words to translate. \n";
	while (state != EXIT && state != SAVE_DICTIONARY)
	{
		std::cout << ">";
		if (!std::getline(std::cin, inStr))
			inStr = "...";
		HandleAction(state, inStrPrev, inStr, dict, dictChanged);
	}

	if (state == SAVE_DICTIONARY)
	{
		std::cout << "The dictionary has been changed. Enter \"Y\" or \"y\" to save.\n";
		if (std::getline(std::cin, inStr) && (inStr == "Y" || inStr == "y"))
		{
			SaveDictionaryToFile(dict, argv[1]);
			std::cout << "Changes to dictionary are saved, exiting.\n";
		}
		else
			std::cout << "Changes to dictionary are not saved, exiting.\n";
	}
	std::cout << "GoodBye.\n";
	return 0;
}
