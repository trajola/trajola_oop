#pragma once
#include "stdafx.h"
#include <sstream>
#include <iomanip>
#include "triangle.h"

CTriangle::CTriangle(CPoint const & vertex1, CPoint const & vertex2, CPoint const & vertex3)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

CTriangle::CTriangle(CPoint const & vertex1, CPoint const & vertex2, CPoint const & vertex3, std::string const & outlineColor, std::string const & fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
	SetOutlineColor(outlineColor);
	SetFillColor(fillColor);
}

double CTriangle::GetPerimeter() const
{
	double side12 = std::hypot(m_vertex1.x - m_vertex2.x, m_vertex1.y - m_vertex2.y);
	double side23 = std::hypot(m_vertex3.x - m_vertex2.x, m_vertex3.y - m_vertex2.y);
	double side13 = std::hypot(m_vertex1.x - m_vertex3.x, m_vertex1.y - m_vertex3.y);
	return side12 + side23 + side13;
}

double CTriangle::GetArea() const
{
	double side12 = std::hypot(m_vertex1.x - m_vertex2.x, m_vertex1.y - m_vertex2.y);
	double side23 = std::hypot(m_vertex3.x - m_vertex2.x, m_vertex3.y - m_vertex2.y);
	double side13 = std::hypot(m_vertex1.x - m_vertex3.x, m_vertex1.y - m_vertex3.y);
	double p = (side12 + side23 + side13) / 2;
	return sqrt(p * (p - side12) * (p - side23) * (p - side13));
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

void CTriangle::AppendStartProperties(std::ostream & strm) const
{
	strm << "Triangle:\n"
		<< "Vertex1 = (" << GetVertex1().x << ", " << GetVertex1().y << ")\n"
		<< "Vertex2 = (" << GetVertex2().x << ", " << GetVertex2().y << ")\n"
		<< "Vertex3 = (" << GetVertex3().x << ", " << GetVertex3().y << ")\n";
}

void CTriangle::Draw(ICanvas & canvas) const
{
	canvas.FillPolygon({GetVertex1(), GetVertex2(), GetVertex3()}, GetFillColor());
	canvas.DrawPolygon({ GetVertex1(), GetVertex2(), GetVertex3() }, GetOutlineColor());
}
