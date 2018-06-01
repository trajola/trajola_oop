#pragma once
#include "stdafx.h"
#include "canvasdrawable.h"

class IShape : public ICanvasDrawable
{
public:
	IShape() : m_outlineColor("#000000") {};
	virtual ~IShape() {};
	virtual double GetPerimeter() const = 0;
	virtual double GetArea() const = 0;
	virtual std::string ToString() const = 0;
	std::string GetOutlineColor() const;
	void SetOutlineColor(std::string const & color);
private:
	std::string m_outlineColor;
};