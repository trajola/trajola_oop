#include "stdafx.h"
#include "ccar.h"

bool CCar::TurnOnEngine()
{
	if (m_engineIsOn)
	{
		m_error = ErrorType::ENGINEON_IS_ALREADY_ON;
		return false;
	}
	m_engineIsOn = true;
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
		return false;
	}
	m_engineIsOn = false;
	m_error = ErrorType::NO_ERROR;
	return true;
}

std::map<int, Bounds> const speedBoundsForGear = {
	{ -1, Bounds{ 0, 20 } },
	{ 0, Bounds{ 0, 150 } },
	{ 1, Bounds{ 0, 30 } },
	{ 2, Bounds{ 20, 50 } },
	{ 3, Bounds{ 30, 60 } },
	{ 4, Bounds{ 40, 90 } },
	{ 5, Bounds{ 50, 150 } }
};

bool CCar::CanSetGear(int gear)
{
	if (gear == 0)
		return true;
	if (gear > 5 || gear < -1)
	{
		m_error = ErrorType::SETGEAR_NOT_IN_RANGE;
		return false;
	}
	if (!m_engineIsOn)
	{
		m_error = ErrorType::SETGEAR_ENGINE_IS_OFF;
		return false;
	}
	if (gear == -1 && m_speed != 0)
	{
		m_error = ErrorType::SETGEAR_BACK_ONLY_0SPEED;
		return false;
	}
	if (gear > 0 && m_direction == MovingDirection::BACKWARD)
	{
		m_error = ErrorType::SETGEAR_MORE0_ONLY_AFTER_GEAR0;
		return false;
	}
	if (speedBoundsForGear.at(gear).min > m_speed || speedBoundsForGear.at(gear).max < m_speed)
	{
		m_error = ErrorType::SETGEAR_SPEED_NOT_SATISFY;
		return false;
	}
	m_error = ErrorType::NO_ERROR;
	return true;
}

bool CCar::SetGear(int gear)
{
	if (!CanSetGear(gear))
		return false;
	m_gear = gear;
	return true;
}

bool CCar::CanSetSpeed(int speed)
{
	if (!m_engineIsOn)
	{
		m_error = ErrorType::SETSPEED_ENGINE_IS_OFF;
		return false;
	}
	if (m_gear == 0 && speed > m_speed)
	{
		m_error = ErrorType::SETSPEED_GEAR0_CANT_ENC;
		return false;
	}
	if (speedBoundsForGear.at(m_gear).min > speed || speedBoundsForGear.at(m_gear).max < speed)
	{
		m_error = ErrorType::SETSPEED_NOT_SATISFY_GEAR;
		return false;
	}
	m_error = ErrorType::NO_ERROR;
	return true;
}

bool CCar::SetSpeed(int speed)
{
	if (!CanSetSpeed(speed))
		return false;
	m_speed = speed;
	if (m_speed == 0)
		m_direction = MovingDirection::INPLACE;
	if (m_speed > 0 && m_gear > 0)
		m_direction = MovingDirection::FORWARD;
	if (m_speed > 0 && m_gear < 0)
		m_direction = MovingDirection::BACKWARD;
	return true;
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

ErrorType CCar::GetErrorCode() const
{
	return m_error;
}
