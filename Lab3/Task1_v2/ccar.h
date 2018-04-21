#pragma once
#include <iostream>

enum class MovingDirection
{
	FORWARD = 1,
	BACKWARD = -1,
	INPLACE = 0
};

enum class ErrorType
{
	NO_ERROR = 0,
	UNKNOWN_ERROR = 50,
	ENGINEON_IS_ALREADY_ON = 10,
	ENGINEOFF_IS_ALREADY_OFF = 20,
	ENGINEOFF_SPEED_NOT_0 = 21,
	ENGINEOFF_GEAR_NOT_0 = 22,
	SETGEAR_ENGINE_IS_OFF = 30,
	SETGEAR_BACK_ONLY_0SPEED = 31,
	SETGEAR_MORE0_ONLY_AFTER_GEAR0 = 32,
	SETGEAR_SPEED_NOT_SATISFY = 33,
	SETSPEED_ENGINE_IS_OFF = 40,
	SETSPEED_GEAR1_0_30 = 41,
	SETSPEED_GEAR2_20_50 = 42,
	SETSPEED_GEAR3_30_60 = 43,
	SETSPEED_GEAR4_40_90 = 44,
	SETSPEED_GEAR5_50_150 = 45,
	SETSPEED_GEAR0_ONLY_DEC = 46,
	SETSPEED_GEARBACK_0_20 = 47,
	
};

class CCar
{
public:
	CCar();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	int GetGear()const;
	int GetSpeed()const;
	MovingDirection GetDirection()const;
	bool EngineIsOn()const;
	int GetErrorCode()const;

private:
	int m_gear;
	int m_speed;
	bool m_engineIsOn;
	MovingDirection m_direction;
	ErrorType m_error;
};