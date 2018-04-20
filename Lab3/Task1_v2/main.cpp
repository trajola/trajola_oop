// Task1_v2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "auto.h"
#include <string>
#include <iostream>

bool GetNumber(std::string const& str, int & number, int minBound, int maxBound)
{
	size_t stoppedAt;
	try
	{
		number = stoi(str, &stoppedAt);
		if (number < minBound || number > maxBound)
		{
			return false;
		}
		if (stoppedAt != str.length())
		{
			return false;
		}
		return true;
	}
	catch (const std::out_of_range&)
	{
		return false;
	}
	catch (const std::invalid_argument&)
	{
		return false;
	}
}


void PrintInfo(CCar car) 
{
	std::cout << "Engine is ";
	if (car.EngineIsOn())
		std::cout << "on, ";
	else
		std::cout << "off, ";
	if (car.GetDirection() == movingDirection::INPLACE)
		std::cout << "inplace, ";
	if (car.GetDirection() == movingDirection::BACKWARD)
		std::cout << "moving backwards, ";
	if (car.GetDirection() == movingDirection::FORWARD)
		std::cout << "moving forwards, ";
	std::cout << "gear " << car.GetGear() << " ";
 	std::cout << "with speed " << car.GetSpeed() << "\n";
}

void PrintResultOfEngineOn(CCar& car)
{
	if (car.TurnOnEngine())
		std::cout << "Engine is on now\n";
	else
		std::cout << "Can't set engine on now, look Info\n";
	return;
}

void PrintResultOfEngineOff(CCar& car)
{
	if (car.TurnOffEngine())
		std::cout << "Engine is off now\n";
	else
		std::cout << "Can't set engine off now, look Info\n";
	return;
}

void PrintResultOfSetGear(CCar& car, std::string const& gearStr)
{
	int gear;
	if (!GetNumber(gearStr, gear, -1, 5))
	{
		std::cout << "Can't set gear, it is out of range -1..5\n";
		return;
	}
	if (car.SetGear(gear))
		std::cout << "Gear is " << gear << " now\n";
	else
		std::cout << "Can't set gear "<< gear << " now, look Info\n";
	return;

}

void PrintResultOfSetSpeed(CCar& car, std::string const& speedStr)
{
	int speed;
	if (!GetNumber(speedStr, speed, 0, 150))
	{
		std::cout << "Can't set speed, it is out of range 0..150\n";
		return;
	}
	if (car.SetSpeed(speed))
		std::cout << "Speed is " << speed << " now\n";
	else
		std::cout << "Can't set speed " << speed << " now, look Info\n";
	return;
}



void HandleAction(std::string const& action, CCar& car)
{
	if (action == "Info")
	{
		PrintInfo(car);
		return;
	}
	if (action == "EngineOn")
	{		
		PrintResultOfEngineOn(car);
		return;
	}
	if (action == "EngineOff")
	{
		PrintResultOfEngineOff(car);
		return;
	}
	if (action.find("SetGear", 0) != std::string::npos)
	{
		PrintResultOfSetGear(car, action.substr(8));
		return;
	}
	if (action.find("SetSpeed", 0) != std::string::npos)
	{
		PrintResultOfSetSpeed(car, action.substr(9));
		return;
	}
	std::cout << "Can't do this action\n";
	return;
}


int main()
{
	CCar car;
	std::string action("");
	std::getline(std::cin, action);
	while (action != "...")
	{
		HandleAction(action, car);
		std::getline(std::cin, action);
	}

	return 0;
}

