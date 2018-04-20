// Task3_v2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "translate.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	Dictionary dict;
	State currentState;
	currentState.dictChanged = true;
	currentState.toDo = Action::WAIT_WORD;
	
	while (currentState.toDo != Action::STOP_AND_EXIT)
	{
		std::cout << ">";
		std::string str;
		std::getline(std::cin, str);

	}
	
	return 0;
}
