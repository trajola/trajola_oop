#pragma once
#include "stdafx.h"
#include "solidshape.h"

void ISolidShape::SetFillColor(std::string const & color)
{
	if (color.length() == 7 && color.at(0) == '#' && color.find_first_not_of("0123456789ABCDEFabcdef", 1) == std::string::npos)
		m_fillColor = move(color);
	return;
}

std::string ISolidShape::GetFillColor() const
{
	return m_fillColor;
}
