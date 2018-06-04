#pragma once
#include "point.h"
#include "shape.h"

class CLineSegment : public CShape
{
public:
	CLineSegment(CPoint const & startPoint, CPoint const & endPoint);
	CLineSegment(CPoint const & startPoint, CPoint const & endPoint, std::string const & color);
	
	double GetPerimeter() const override;
	double GetArea() const override;
	
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

	void AppendStartProperties(std::ostream & strm) const override;
	void AppendFinishProperties(std::ostream & strm) const override;

	void  Draw(ICanvas & canvas) const override;

private:
	CPoint m_startPoint, m_endPoint;
};
