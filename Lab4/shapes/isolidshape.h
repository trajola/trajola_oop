#pragma once
#include "shape.h"

class ISolidShape : public CShape
{
public:
	virtual ~ISolidShape() {};
	virtual	std::string GetFillColor() const = 0;
};