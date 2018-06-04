#pragma once
#include "stdafx.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "rectangle.h"

CRectangle::CRectangle(CPoint const & vertex1, CPoint const & vertex2)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
{
}

CRectangle::CRectangle(CPoint const & vertex1, CPoint const & vertex2, std::string const & outlineColor, std::string const & fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
{
	SetOutlineColor(outlineColor);
	SetFillColor(fillColor);
}

double CRectangle::GetPerimeter() const
{
	double side1 = std::hypot(0, m_vertex1.y - m_vertex2.y);
	double side2 = std::hypot(m_vertex1.x - m_vertex2.x, 0);
	return 2 * (side1 + side2);
}

double CRectangle::GetArea() const
{
	double side1 = std::hypot(0, m_vertex1.y - m_vertex2.y);
	double side2 = std::hypot(m_vertex1.x - m_vertex2.x, 0);
	return side1 * side2;
}

CPoint CRectangle::GetLeftTop() const
{
	return {std::min(m_vertex1.x, m_vertex2.x), std::min(m_vertex1.y, m_vertex2.y) };
}

CPoint CRectangle::GetRightBottom() const
{
	return { std::max(m_vertex1.x, m_vertex2.x), std::max(m_vertex1.y, m_vertex2.y) };
}

void CRectangle::AppendStartProperties(std::ostream & strm) const
{
	strm << "Rectangle:\n"
		<< "LeftTop = (" << GetLeftTop().x << ", " << GetLeftTop().y << ")\n"
		<< "RightBottom = (" << GetRightBottom().x << ", " << GetRightBottom().y << ")\n";
}

void CRectangle::Draw(ICanvas & canvas) const
{
	canvas.FillPolygon({ { m_vertex1.x, m_vertex1.y },	
					 	 { m_vertex1.x, m_vertex2.y },
						 { m_vertex2.x, m_vertex2.y }, 
						 { m_vertex2.x, m_vertex1.y } }, GetFillColor());

	canvas.DrawPolygon({ { m_vertex1.x, m_vertex1.y },
		{ m_vertex1.x, m_vertex2.y },
		{ m_vertex2.x, m_vertex2.y },
		{ m_vertex2.x, m_vertex1.y } }, GetOutlineColor());
}