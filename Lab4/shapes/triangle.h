#pragma once
#include "point.h"
#include "solidshape.h"
#include "canvasdrawable.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(CPoint const & vertex1, CPoint const & vertex2, CPoint const & vertex3);
	CTriangle(CPoint const & vertex1, CPoint const & vertex2, CPoint const & vertex3, std::string const & outlineColor, std::string const & fillColor);
	double GetPerimeter() const override;
	double GetArea() const override;
	std::string ToString() const override;
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
	void Draw(ICanvas & canvas) const override;
private:
	CPoint m_vertex1, m_vertex2, m_vertex3;
};
