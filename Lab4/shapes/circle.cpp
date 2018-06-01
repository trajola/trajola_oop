#pragma once
#include "stdafx.h"
#define _USE_MATH_DEFINES
#include "circle.h"
#include <math.h>
#include "canvasdrawable.h"

CCircle::CCircle(CPoint const & center, double radius)
	: m_center(center)
	, m_radius(radius)
{
}

CCircle::CCircle(CPoint const & center, double radius, std::string const & outlineColor, std::string const & fillColor)
	: m_center(center)
	, m_radius(radius)
{
	SetOutlineColor(outlineColor);
	SetFillColor(fillColor);
}

double CCircle::GetPerimeter() const
{
	return 2 * m_radius * M_PI;
}

double CCircle::GetArea() const
{
	return pow(m_radius, 2) * M_PI;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

std::string CCircle::ToString() const
{
	std::ostringstream str;
	str << std::fixed << std::setprecision(3);
	str << "Circle:\n"
		<< "Center = (" << GetCenter().x << ", " << GetCenter().y << ")\n"
		<< "Radius = " << GetRadius() << "\n"
		<< "Perimeter = " << GetPerimeter() << "\n"
		<< "Area = " << GetArea() << "\n"
		<< "OutlineColor = " << GetOutlineColor() << "\n"
		<< "FillColor = " << GetFillColor() << "\n";
	return str.str();
}

void CCircle::Draw(ICanvas & canvas) const
{
	canvas.FillCircle(m_center, m_radius, GetFillColor());
	canvas.DrawCircle(m_center, m_radius, GetOutlineColor());
}