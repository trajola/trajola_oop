#pragma once
#include "stdafx.h"
#include "canvas.h"

class CCanvas : public ICanvas
{
public:
	CCanvas(std::string const & outFileName);
	~CCanvas();
	void DrawLine(CPoint const & from, CPoint const & to, std::string const & lineColor) override;
	void FillCircle(CPoint const & center, double radius, std::string const & fillColor) override;
	void DrawCircle(CPoint const & center, double radius, std::string const & lineColor) override;
	void FillPolygon(std::vector<CPoint> const & points, std::string const & lineColor, std::string const & fillColor) override;

private:
	std::ofstream m_outFile;
};