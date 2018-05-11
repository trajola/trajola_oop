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



void HandleAction(StateType& state, std::string const& inStr, Dictionary& dict)
{
	if (state == TRANSLATE)
	{
		if (inStr == "...")
		{
			state = EXIT;
			return;
		}
		std::string translation;
		if (Translate(inStr, translation, dict))
			std::cout << translation << "\n";
		else
		{
			//state = ADD_WORD_TO_DICTIONARY;
			std::cout << "don't know" << "\n";
		}
	}

	return;
}



int main(int argc, char* argv[])
{
	Dictionary dict;
	ReadDictionaryFromFile(dict, argv[1]);
	bool dictChanged = true;
	StateType state = TRANSLATE;
	while (state != EXIT)
	{
		std::cout << ">";
		std::string inStr;
		std::getline(std::cin, inStr);
		HandleAction(state, inStr, dict);
	}
	return 0;
}
