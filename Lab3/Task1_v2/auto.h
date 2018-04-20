#pragma once
#include <iostream>

enum class movingDirection
{
	FORWARD = 1,
	BACKWARD = -1,
	INPLACE = 0
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
	movingDirection GetDirection()const;
	bool EngineIsOn()const;

private:
	int m_gear;
	int m_speed;
	bool m_engineIsOn;
	movingDirection m_direction;
};