#pragma once
#include "icanvasdrawable.h"

class IShape : public ICanvasDrawable
{
public:
	virtual ~IShape() {};

	virtual double GetPerimeter() const = 0;
	virtual double GetArea() const = 0;
	virtual std::string GetOutlineColor() const = 0;
	virtual std::string ToString() const = 0;

};