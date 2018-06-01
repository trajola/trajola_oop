#pragma once
#include "shape.h"
#include "point.h"
#include "canvasdrawable.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(CPoint const & startPoint, CPoint const & endPoint);
	CLineSegment(CPoint const & startPoint, CPoint const & endPoint, std::string const & color);
	double GetPerimeter() const override;
	double GetArea() const override;
	std::string ToString() const override;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
	void  Draw(ICanvas & canvas) const override;
private:
	CPoint m_startPoint, m_endPoint;
};
