#pragma once
#include <fstream>
#include "icanvas.h"

class CCanvas : public ICanvas
{
public:
	CCanvas(std::string const & outFileName);
	~CCanvas();

	void DrawLine(CPoint const & from, CPoint const & to, std::string const & lineColor) override final;
	
	void FillCircle(CPoint const & center, double radius, std::string const & fillColor) override final;
	void DrawCircle(CPoint const & center, double radius, std::string const & lineColor) override final;
	
	void FillPolygon(std::vector<CPoint> const & points, std::string const & fillColor) override final;
	void DrawPolygon(std::vector<CPoint> const & points, std::string const & lineColor) override final;

private:
	std::ofstream m_outFile;
};