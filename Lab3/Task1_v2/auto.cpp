#include "stdafx.h"
#include "auto.h"

CCar::CCar()
{
	m_engineIsOn = false;
	m_direction = movingDirection::INPLACE;
	m_gear = 0;
	m_speed = 0;
}

bool CCar::TurnOnEngine()
{
	if (m_engineIsOn)
	{
		return false;
	}
	m_engineIsOn = true;
	m_gear = 0;
	m_speed = 0;
	m_direction = movingDirection::INPLACE;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (!m_engineIsOn || m_speed != 0 || m_gear != 0)
	{
		return false;
	}
	m_engineIsOn = false;
	m_gear = 0;
	m_speed = 0;
	m_direction = movingDirection::INPLACE;
	return true;
}

bool CCar::SetGear(int gear)
{
	if (gear == 0 ||
		m_engineIsOn &&	(
		gear == -1 && m_speed == 0 ||
		gear == 1 && m_speed >= 0 && m_speed <= 30 && (m_direction == movingDirection::FORWARD || m_direction == movingDirection::INPLACE)||
		gear == 2 && m_speed >= 20 && m_speed <= 50 && m_direction == movingDirection::FORWARD ||
		gear == 3 && m_speed >= 30 && m_speed <= 60 && m_direction == movingDirection::FORWARD || 
		gear == 4 && m_speed >= 40 && m_speed <= 90 && m_direction == movingDirection::FORWARD ||
		gear == 5 && m_speed >= 50 && m_speed <= 150 && m_direction == movingDirection::FORWARD))
	{
		m_gear = gear;
		return true;
	}
	return false;
}

bool CCar::SetSpeed(int speed)
{
	if (m_engineIsOn && (
		m_gear == -1 && speed >= 0 && speed <= 20 || 
		m_gear == 0 && speed >= 0 && (speed < m_speed || speed == 0) || 
		m_gear == 1 && speed >= 0 && speed <= 30 || 
		m_gear == 2 && speed >= 20 && speed <= 50 || 
		m_gear == 3 && speed >= 30 && speed <= 60 || 
		m_gear == 4 && speed >= 40 && speed <= 90 || 
		m_gear == 5 && speed >= 50 && speed <= 150))
	{
		m_speed = speed;
		if (m_speed == 0)
			m_direction = movingDirection::INPLACE;
		if (m_speed > 0 && m_gear > 0)
			m_direction = movingDirection::FORWARD;
		if (m_speed > 0 && m_gear < 0)
			m_direction = movingDirection::BACKWARD;
		return true;
	}
	return false;
}

int CCar::GetGear() const
{
	return m_gear;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

movingDirection CCar::GetDirection()const
{
	return m_direction;
}

bool CCar::EngineIsOn() const
{
	return m_engineIsOn;
}
