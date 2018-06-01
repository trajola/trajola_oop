#pragma once
#include "stdafx.h"
#include "canvas-svg.h"

CCanvas::CCanvas(std::string const & outStreamName)
{
	m_outFile.open(outStreamName);
	if (m_outFile.is_open())
	{
		std::string header = 
			"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"
			"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n"
			" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n"
			"<svg width=\"1000\" height=\"1000\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n"
			"<title>Picture for Lab4</title>\n";
		m_outFile << header;
	}
}

CCanvas::~CCanvas()
{
	m_outFile << "</svg>";
	m_outFile.close();
}

void CCanvas::DrawLine(CPoint const & from, CPoint const & to, std::string const & lineColor)
{	
	m_outFile << std::fixed << std::setprecision(0);
	m_outFile << "<line x1=\"" << from.x << "\"";
	m_outFile << " y1=\"" << from.y << "\"";
	m_outFile << " x2=\"" << to.x << "\"";
	m_outFile << " y2=\"" << to.y << "\"";
	m_outFile << " stroke=\"" << lineColor << "\" stroke-width=\"1\" />\n";
}

void CCanvas::FillCircle(CPoint const & center, double radius, std::string const & fillColor)
{
	m_outFile << std::fixed << std::setprecision(0);
	m_outFile << "<circle cx=\"" << center.x << "\"";
	m_outFile << " cy=\"" << center.y << "\"";
	m_outFile << " r=\"" << radius << "\"";
	m_outFile << " fill=\"" << fillColor << "\" />\n";
}

void CCanvas::DrawCircle(CPoint const & center, double radius, std::string const & lineColor)
{
	m_outFile << std::fixed << std::setprecision(0);
	m_outFile << "<circle cx=\"" << center.x << "\"";
	m_outFile << " cy=\"" << center.y << "\"";
	m_outFile << " r=\"" << radius << "\"";
	m_outFile << " fill=\"none\"";
	m_outFile << " stroke=\"" << lineColor << "\" stroke-width=\"1\" />\n";
}

void CCanvas::FillPolygon(std::vector<CPoint> const & points, std::string const & lineColor, std::string const & fillColor)
{
	m_outFile << std::fixed << std::setprecision(0);
	m_outFile << "<polygon points=\"";
	for (auto point : points)
		m_outFile << point.x << "," << point.y << " ";
	m_outFile << "\"";
	m_outFile << " fill=\"" << fillColor << "\"";
	m_outFile << " stroke=\"" << lineColor << "\" stroke-width=\"1\" />\n";
}
