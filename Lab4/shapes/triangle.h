#pragma once
#include "point.h"
#include "solidshape.h"

class CTriangle : public CSolidShape
{
public:
	CTriangle(CPoint const & vertex1, CPoint const & vertex2, CPoint const & vertex3);
	CTriangle(CPoint const & vertex1, CPoint const & vertex2, CPoint const & vertex3, std::string const & outlineColor, std::string const & fillColor);
	
	double GetPerimeter() const override final;
	double GetArea() const override final;
	
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

	void AppendStartProperties(std::ostream & strm) const override final;

	void Draw(ICanvas & canvas) const override final;

private:
	CPoint m_vertex1, m_vertex2, m_vertex3;
};
