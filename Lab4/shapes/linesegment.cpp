#pragma once
#include "stdafx.h"
#include "linesegment.h"
#include "canvasdrawable.h"

CLineSegment::CLineSegment(CPoint const & startPoint, CPoint const & endPoint)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
{
}

CLineSegment::CLineSegment(CPoint const & startPoint, CPoint const & endPoint, std::string const &color)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
{
	SetOutlineColor(color);
}

double CLineSegment::GetPerimeter() const
{
	return std::hypot(m_startPoint.x - m_endPoint.x, m_startPoint.y - m_endPoint.y);
}

double CLineSegment::GetArea() const
{
	return 0;
}

std::string CLineSegment::ToString() const
{
	std::ostringstream str;
	str << std::fixed << std::setprecision(3);
	str << "LineSegment:\n"
		<< "StartPoint = (" << GetStartPoint().x << ", " << GetStartPoint().y << ")\n"
		<< "EndPoint = (" << GetEndPoint().x << ", " << GetEndPoint().y << ")\n"
		<< "Perimeter = " << GetPerimeter() << "\n"
		<< "Area = " << GetArea() << "\n"
		<< "Color = " << GetOutlineColor() << "\n";
	return str.str();
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

void CLineSegment::Draw(ICanvas & canvas) const
{
	canvas.DrawLine(m_startPoint, m_endPoint, GetOutlineColor());
}
