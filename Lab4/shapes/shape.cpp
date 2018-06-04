#pragma once
#include "stdafx.h"
#include "shape.h"

void CShape::SetOutlineColor(std::string const & color)
{
	if (color.length() == 7 && color.at(0) == '#' && color.find_first_not_of("0123456789ABCDEFabcdef", 1) == std::string::npos)
		m_outlineColor = move(color);
	return;
}

std::string CShape::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CShape::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(3);
	AppendStartProperties(strm);
	strm << "Perimeter = " << GetPerimeter() << "\n"
		<< "Area = " << GetArea() << "\n"
		<< "OutlineColor = " << GetOutlineColor() << "\n";
	AppendFinishProperties(strm);
	return strm.str();
}