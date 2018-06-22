#pragma once
#include "point.h"
#include "solidshape.h"

class CRectangle final : public CSolidShape
{
public:
	CRectangle(CPoint const & vertex1, CPoint const & vertex2);
	CRectangle(CPoint const & vertex1, CPoint const & vertex2, std::string const & outlineColor, std::string const & fillColor);

	double GetPerimeter() const override;
	double GetArea() const override;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;

	void Draw(ICanvas & canvas) const override;

private:
	void AppendStartProperties(std::ostream & strm) const override;

	CPoint m_vertex1, m_vertex2;
};
