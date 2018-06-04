#pragma once
#include "stdafx.h"
#include <sstream>
#include <iomanip>
#include "linesegment.h"

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


void CLineSegment::AppendStartProperties(std::ostream & strm) const
{
	strm << "LineSegment:\n"
		<< "StartPoint = (" << GetStartPoint().x << ", " << GetStartPoint().y << ")\n"
		<< "EndPoint = (" << GetEndPoint().x << ", " << GetEndPoint().y << ")\n";
}

void CLineSegment::AppendFinishProperties(std::ostream & strm) const
{
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
