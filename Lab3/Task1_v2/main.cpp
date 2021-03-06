// Task1_v2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ccar.h"
#include <iostream>
#include <string>

std::string GetErrorMessage(CCar const& car)
{
	ErrorType error = car.GetErrorCode();
	switch (error)
	{
	case ErrorType::NO_ERROR:
		return "No error";
	case ErrorType::ENGINEON_IS_ALREADY_ON:
		return "The engine is already On";
	case ErrorType::ENGINEOFF_IS_ALREADY_OFF:
		return "The engine is already Off";
	case ErrorType::ENGINEOFF_SPEED_NOT_0:
		return "Can't turn off engine while speed not 0";
	case ErrorType::ENGINEOFF_GEAR_NOT_0:
		return "Can't turn off engine while gear not 0";
	case ErrorType::SETGEAR_BACK_ONLY_0SPEED:
		return "Can set gear -1 at only 0 speed";
	case ErrorType::SETGEAR_ENGINE_IS_OFF:
		return "Can set this gear only when engine is on";
	case ErrorType::SETGEAR_MORE0_ONLY_AFTER_GEAR0:
		return "Can set this gear only after gear 0 and appropriate speed";
	case ErrorType::SETGEAR_SPEED_NOT_SATISFY:
		return "To set this gear set appropriate speed, use InfoSpeedGear for information";
	case ErrorType::SETSPEED_ENGINE_IS_OFF:
		return "Can't set speed while engine is off";
	case ErrorType::SETSPEED_GEAR0_CANT_ENC:
		return "Can't encrease speed at gear0";
	case ErrorType::SETSPEED_NOT_SATISFY_GEAR:
		return "Speed doesn't satisfy this gear, use InfoSpeedGear for information";
	}
	return "Don't know this error";
}

bool GetNumber(std::string const& str, int& number, int minBound, int maxBound)
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

void PrintInfo(CCar const& car)
{
	std::cout << ">>Engine is ";
	if (car.EngineIsOn())
		std::cout << "on, ";
	else
		std::cout << "off, ";
	if (car.GetDirection() == MovingDirection::INPLACE)
		std::cout << "inplace, ";
	if (car.GetDirection() == MovingDirection::BACKWARD)
		std::cout << "moving backwards, ";
	if (car.GetDirection() == MovingDirection::FORWARD)
		std::cout << "moving forwards, ";
	std::cout << "gear " << car.GetGear() << " ";
	std::cout << "with speed " << car.GetSpeed() << "\n";
}

void PrintInfoSpeedGear()
{
	std::cout << ">>Speed info:\n";
	for (int gear = -1; gear <= 5; gear++)
	{
		std::cout << ">>gear " << gear << " : " << speedBoundsForGear.at(gear).min << " .. "
			<< speedBoundsForGear.at(gear).max;
		if (gear == 0)
			std::cout << "(can't encrease)";
		std::cout << "\n";
	}
}

void PrintResultOfEngineOn(CCar& car)
{
	if (car.TurnOnEngine())
		std::cout << ">>Engine is on now\n";
	else
		std::cout << ">>Can't set engine on now. " << GetErrorMessage(car) << "\n";
	return;
}

void PrintResultOfEngineOff(CCar& car)
{
	if (car.TurnOffEngine())
		std::cout << ">>Engine is off now\n";
	else
		std::cout << ">>Can't set engine off now. " << GetErrorMessage(car) << "\n";
	return;
}

void PrintResultOfSetGear(CCar& car, std::string const& gearStr)
{
	int gear;
	if (!GetNumber(gearStr, gear, -1, 5))
	{
		std::cout << ">>Can't set gear, it is out of range -1..5\n";
		return;
	}
	if (car.SetGear(gear))
		std::cout << ">>Gear is " << gear << " now\n";
	else
		std::cout << ">>Can't set gear " << gear << " now. " << GetErrorMessage(car) << "\n";
	return;
}

void PrintResultOfSetSpeed(CCar& car, std::string const& speedStr)
{
	int speed;
	if (!GetNumber(speedStr, speed, 0, 150))
	{
		std::cout << ">>Can't set speed, it is out of range 0..150\n";
		return;
	}
	if (car.SetSpeed(speed))
		std::cout << ">>Speed is " << speed << " now\n";
	else
		std::cout << ">>Can't set speed " << speed << " now. " << GetErrorMessage(car) << "\n";
	return;
}

void HandleAction(std::string const& action, CCar& car)
{
	if (action == "Info")
	{
		PrintInfo(car);
		return;
	}
	if (action == "InfoSpeedGear")
	{
		PrintInfoSpeedGear();
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
		PrintResultOfSetGear(car, action.substr(7));
		return;
	}
	if (action.find("SetSpeed", 0) != std::string::npos)
	{
		PrintResultOfSetSpeed(car, action.substr(8));
		return;
	}
	std::cout << "Can't do this action\n";
	return;
}

int main()
{
	CCar car;
	std::string action;
	std::cout << ">>Car commands: Info, InfoSpeedGear, EngineOn, EngineOff, SetSpeed<speed>, SetGear<gear>\n>>Type ... for exit \n";
	if (!std::getline(std::cin, action))
		action = "...";
	while (action != "...")
	{
		HandleAction(action, car);
		if (!std::getline(std::cin, action))
			action = "...";
	}

	return 0;
}
