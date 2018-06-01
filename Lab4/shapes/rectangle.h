#pragma once
#include "point.h"
#include "solidshape.h"
#include "canvasdrawable.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(CPoint const & vertex1, CPoint const & vertex2);
	CRectangle(CPoint const & vertex1, CPoint const & vertex2, std::string const & outlineColor, std::string const & fillColor);
	double GetPerimeter() const override;
	double GetArea() const override;
	std::string ToString() const override;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	void Draw(ICanvas & canvas) const override;
private:
	CPoint m_vertex1, m_vertex2;
};
