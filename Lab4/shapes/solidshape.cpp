#pragma once
#include "stdafx.h"
#include "solidshape.h"

void CSolidShape::SetFillColor(std::string const & color)
{
	if (color.length() == 7 && color.at(0) == '#' && color.find_first_not_of("0123456789ABCDEFabcdef", 1) == std::string::npos)
		m_fillColor = move(color);
	return;
}

std::string CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

void CSolidShape::AppendFinishProperties(std::ostream & strm) const
{
	strm << "FillColor = " << GetFillColor() << "\n";
}