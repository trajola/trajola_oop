#pragma once
#include "point.h"
#include "solidshape.h"

class CCircle : public CSolidShape
{
public:
	CCircle(CPoint const & center, double radius);
	CCircle(CPoint const & center, double radius, std::string const & outlineColor, std::string const & fillColor);
	
	double GetPerimeter() const override;
	double GetArea() const override;

	CPoint GetCenter() const;
	double GetRadius() const;

	void AppendStartProperties(std::ostream & strm) const override;

	void Draw(ICanvas & canvas) const override;

private:
	CPoint m_center;
	double m_radius;
};
