#pragma once
#include "stdafx.h"
#include "shape.h"

class ISolidShape : public IShape
{
public:
	ISolidShape() : m_fillColor("#FFFFFF") {};
	virtual ~ISolidShape() {};
	std::string GetFillColor() const;
	void SetFillColor(std::string const & color);
private:
	std::string m_fillColor;
};