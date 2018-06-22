#pragma once
#include "isolidshape.h"

class CSolidShape : public ISolidShape
{
public:
	CSolidShape() : m_fillColor("#FFFFFF") {};

	std::string GetFillColor() const override final;
	void SetFillColor(std::string const & color);
	
private:
	void AppendFinishProperties(std::ostream & strm) const override final;

	std::string m_fillColor;
};