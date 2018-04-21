#include "stdafx.h"
#include "ccar.h"

CCar::CCar()
{
	m_engineIsOn = false;
	m_direction = MovingDirection::INPLACE;
	m_gear = 0;
	m_speed = 0;
}

bool CCar::TurnOnEngine()
{
	if (m_engineIsOn)
	{
		m_error = ErrorType::ENGINEON_IS_ALREADY_ON;
		return false;
	}
	m_engineIsOn = true;
	m_gear = 0;
	m_speed = 0;
	m_direction = MovingDirection::INPLACE;
	m_error = ErrorType::NO_ERROR;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (!m_engineIsOn || m_speed != 0 || m_gear != 0)
	{
		if (!m_engineIsOn)
			m_error = ErrorType::ENGINEOFF_IS_ALREADY_OFF;
		else if (m_speed != 0)
			m_error = ErrorType::ENGINEOFF_SPEED_NOT_0;
		else if (m_gear != 0)
			m_error = ErrorType::ENGINEOFF_GEAR_NOT_0;
		else
			m_error = ErrorType::UNKNOWN_ERROR;
		return false;
	}
	m_engineIsOn = false;
	m_gear = 0;
	m_speed = 0;
	m_direction = MovingDirection::INPLACE;
	m_error = ErrorType::NO_ERROR;
	return true;
}

bool CCar::SetGear(int gear)
{
	if (gear == 0 || 
		m_engineIsOn && 
		(gear == -1 && m_speed == 0 || 
		gear == 1 && m_speed >= 0 && m_speed <= 30 && (m_direction == MovingDirection::FORWARD || m_direction == MovingDirection::INPLACE) ||
		gear == 2 && m_speed >= 20 && m_speed <= 50 && m_direction == MovingDirection::FORWARD || 
		gear == 3 && m_speed >= 30 && m_speed <= 60 && m_direction == MovingDirection::FORWARD || 
		gear == 4 && m_speed >= 40 && m_speed <= 90 && m_direction == MovingDirection::FORWARD || 
		gear == 5 && m_speed >= 50 && m_speed <= 150 && m_direction == MovingDirection::FORWARD))
	{
		m_gear = gear;
		m_error = ErrorType::NO_ERROR;
		return true;
	}
	if (!m_engineIsOn)
		m_error = ErrorType::SETGEAR_ENGINE_IS_OFF;
	else if (gear == -1 && m_speed != 0)
		m_error = ErrorType::SETGEAR_BACK_ONLY_0SPEED;
	else if (gear > 0 && m_direction == MovingDirection::BACKWARD)
		m_error = ErrorType::SETGEAR_MORE0_ONLY_AFTER_GEAR0;
	else
		m_error = ErrorType::SETGEAR_SPEED_NOT_SATISFY;
	return false;
}

bool CCar::SetSpeed(int speed)
{
	if (m_engineIsOn && 
		(m_gear == -1 && speed >= 0 && speed <= 20 || 
		m_gear == 0 && speed >= 0 && (speed < m_speed || speed == 0) || 
		m_gear == 1 && speed >= 0 && speed <= 30 || 
		m_gear == 2 && speed >= 20 && speed <= 50 || 
		m_gear == 3 && speed >= 30 && speed <= 60 || 
		m_gear == 4 && speed >= 40 && speed <= 90 || 
		m_gear == 5 && speed >= 50 && speed <= 150))
	{
		m_speed = speed;
		if (m_speed == 0)
			m_direction = MovingDirection::INPLACE;
		if (m_speed > 0 && m_gear > 0)
			m_direction = MovingDirection::FORWARD;
		if (m_speed > 0 && m_gear < 0)
			m_direction = MovingDirection::BACKWARD;
		m_error = ErrorType::NO_ERROR;
		return true;
	}
	if (!m_engineIsOn)
		m_error = ErrorType::SETSPEED_ENGINE_IS_OFF;
	else if (m_gear == -1)
		m_error = ErrorType::SETSPEED_GEARBACK_0_20;
	else if (m_gear == 0)
		m_error = ErrorType::SETSPEED_GEAR0_ONLY_DEC;
	else if (m_gear == 1)
		m_error = ErrorType::SETSPEED_GEAR1_0_30;
	else if (m_gear == 2)
		m_error = ErrorType::SETSPEED_GEAR2_20_50;
	else if (m_gear == 3)
		m_error = ErrorType::SETSPEED_GEAR3_30_60;
	else if (m_gear == 4)
		m_error = ErrorType::SETSPEED_GEAR4_40_90;
	else if (m_gear == 5)
		m_error = ErrorType::SETSPEED_GEAR5_50_150;
	else
		m_error = ErrorType::UNKNOWN_ERROR;
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

MovingDirection CCar::GetDirection() const
{
	return m_direction;
}

bool CCar::EngineIsOn() const
{
	return m_engineIsOn;
}

int CCar::GetErrorCode() const
{
	return static_cast<int>(m_error);
}
