#pragma once
#include "isolidshape.h"

class CSolidShape : public ISolidShape
{
public:
	CSolidShape() : m_fillColor("#FFFFFF") {};

	std::string GetFillColor() const;
	void SetFillColor(std::string const & color);
	
	void AppendFinishProperties(std::ostream & strm) const override;

private:
	std::string m_fillColor;
};