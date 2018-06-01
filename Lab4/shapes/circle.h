#pragma once
#include "point.h"
#include "solidshape.h"
#include "canvasdrawable.h"

class CCircle : public ISolidShape
{
public:
	CCircle(CPoint const & center, double radius);
	CCircle(CPoint const & center, double radius, std::string const & outlineColor, std::string const & fillColor);
	double GetPerimeter() const override;
	double GetArea() const override;
	std::string ToString() const override;
	CPoint GetCenter() const;
	double GetRadius() const;
	void Draw(ICanvas & canvas) const override;
private:
	CPoint m_center;
	double m_radius;
};
