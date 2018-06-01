#pragma once
#include "stdafx.h"
#include "shape.h"


void IShape::SetOutlineColor(std::string const & color)
{
	if (color.length() == 7 && color.at(0) == '#' && color.find_first_not_of("0123456789ABCDEFabcdef", 1) == std::string::npos)
		m_outlineColor = move(color);
	return;
}

std::string IShape::GetOutlineColor() const
{
	return m_outlineColor;
}