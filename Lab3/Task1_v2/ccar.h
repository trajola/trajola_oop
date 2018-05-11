#pragma once
#include <iostream>
#include <map>

enum class MovingDirection
{
	FORWARD = 1,
	BACKWARD = -1,
	INPLACE = 0
};

enum class ErrorType
{
	NO_ERROR,
	ENGINEON_IS_ALREADY_ON,
	ENGINEOFF_IS_ALREADY_OFF,
	ENGINEOFF_SPEED_NOT_0,
	ENGINEOFF_GEAR_NOT_0,
	SETGEAR_NOT_IN_RANGE,
	SETGEAR_ENGINE_IS_OFF,
	SETGEAR_BACK_ONLY_0SPEED,
	SETGEAR_MORE0_ONLY_AFTER_GEAR0,
	SETGEAR_SPEED_NOT_SATISFY,
	SETSPEED_ENGINE_IS_OFF,
	SETSPEED_NOT_SATISFY_GEAR,
	SETSPEED_GEAR0_CANT_ENC
};

struct Bounds
{
	int min, max;
};

extern std::map<int, Bounds> const speedBoundsForGear;

class CCar
{
public:
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	int GetGear() const;
	int GetSpeed() const;
	MovingDirection GetDirection() const;
	bool EngineIsOn() const;
	ErrorType GetErrorCode() const;

private:
	bool CanSetGear(int gear);
	bool CanSetSpeed(int speed);
	int m_gear = 0;
	int m_speed = 0;
	bool m_engineIsOn = false;
	MovingDirection m_direction = MovingDirection::INPLACE;
	ErrorType m_error = ErrorType::NO_ERROR;
};
