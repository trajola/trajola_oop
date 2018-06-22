#pragma once
#include "stdafx.h"
#include <functional>
#include <sstream>
#include "shapesreader.h"
#include "shape.h"
#include "linesegment.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"

CShapesReader::CShapesReader(std::istream &input)
	: m_actions({
		{ "line", std::bind(&CShapesReader::ReadLine, this, std::placeholders::_1) },
		{ "circle", std::bind(&CShapesReader::ReadCircle, this, std::placeholders::_1) },
		{ "triangle", std::bind(&CShapesReader::ReadTriangle, this, std::placeholders::_1) },
		{ "rectangle", std::bind(&CShapesReader::ReadRectangle, this, std::placeholders::_1) }
		}),
	m_input(input)
{
}

std::shared_ptr<CShape> CShapesReader::ReadShape() const
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string shape;
	strm >> shape;

	auto action = m_actions.find(shape);
	if (action != m_actions.end())
	{
		return action->second(strm);
	}
	return nullptr;
}

std::shared_ptr<CShape> CShapesReader::ReadLine(std::istream &args) const
{
	CPoint startPoint, endPoint;
	std::string outlineColor, input;

	try
	{
		args >> input;
		startPoint.x = std::stod(input);
		input.clear();
		args >> input;
		startPoint.y = std::stod(input);
		input.clear();

		args >> input;
		endPoint.x = std::stod(input);
		input.clear();
		args >> input;
		endPoint.y = std::stod(input);

		if (!args.eof())
			args >> outlineColor;
	}
	catch (const std::exception&)
	{
		return nullptr;
	}

	if (!outlineColor.empty())		
		return std::make_shared<CLineSegment>(startPoint, endPoint, outlineColor);
	else
		return std::make_shared<CLineSegment>(startPoint, endPoint);
}

std::shared_ptr<CShape> CShapesReader::ReadCircle(std::istream &args) const
{
	CPoint center;
	double radius;
	std::string outlineColor, fillColor, input;

	try
	{
		args >> input;
		center.x = std::stod(input);
		input.clear();
		args >> input;
		center.y = std::stod(input);
		input.clear();
		args >> input;
		radius = std::stod(input);
		
		if (!args.eof())
		{
			args >> outlineColor;
			args >> fillColor;
		}
	}
	catch (const std::exception&)
	{
		return nullptr;
	}
	if (!fillColor.empty())
		return std::make_shared<CCircle>(center, radius, outlineColor, fillColor);
	else
		return std::make_shared<CCircle>(center, radius);
}


std::shared_ptr<CShape> CShapesReader::ReadTriangle(std::istream &args) const
{
	CPoint vertex1, vertex2, vertex3;
	std::string outlineColor, fillColor, input;

	try
	{
		args >> input;
		vertex1.x = std::stod(input);
		input.clear();
		args >> input;
		vertex1.y = std::stod(input);
		input.clear();

		args >> input;
		vertex2.x = std::stod(input);
		input.clear();
		args >> input;
		vertex2.y = std::stod(input);
		input.clear();

		args >> input;
		vertex3.x = std::stod(input);
		input.clear();
		args >> input;
		vertex3.y = std::stod(input);

		if (!args.eof())
		{
			args >> outlineColor;
			args >> fillColor;
		}
	}

	catch (const std::exception&)
	{
		return nullptr;
	}
	if (!fillColor.empty())
		return std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
	else
		return std::make_shared<CTriangle>(vertex1, vertex2, vertex3);
}

std::shared_ptr<CShape> CShapesReader::ReadRectangle(std::istream &args) const
{
	CPoint vertex1, vertex2;
	std::string outlineColor, fillColor, input;

	try
	{
		args >> input;
		vertex1.x = std::stod(input);
		input.clear();
		args >> input;
		vertex1.y = std::stod(input);
		input.clear();

		args >> input;
		vertex2.x = std::stod(input);
		input.clear();
		args >> input;
		vertex2.y = std::stod(input);
		input.clear();

		if (!args.eof())
		{
			args >> outlineColor;
			args >> fillColor;
		}
	}

	catch (const std::exception&)
	{
		return nullptr;
	}
	if (!fillColor.empty())
		return std::make_shared<CRectangle>(vertex1, vertex2, outlineColor, fillColor);
	else
		return std::make_shared<CRectangle>(vertex1, vertex2);
}
