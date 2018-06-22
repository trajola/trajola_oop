#pragma once
#include "point.h"
#include "solidshape.h"

class CRectangle : public CSolidShape
{
public:
	CRectangle(CPoint const & vertex1, CPoint const & vertex2);
	CRectangle(CPoint const & vertex1, CPoint const & vertex2, std::string const & outlineColor, std::string const & fillColor);

	double GetPerimeter() const override final;
	double GetArea() const override final;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;

	void AppendStartProperties(std::ostream & strm) const override final;

	void Draw(ICanvas & canvas) const override final;

private:
	CPoint m_vertex1, m_vertex2;
};
