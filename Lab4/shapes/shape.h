#pragma once
#include "ishape.h"

class CShape : public IShape
{
public:
	CShape() : m_outlineColor("#000000") {};
	
	std::string GetOutlineColor() const override;
	void SetOutlineColor(std::string const & color);

	std::string ToString() const;

protected:
	virtual void AppendStartProperties(std::ostream & strm) const = 0;
	virtual void AppendFinishProperties(std::ostream & strm) const = 0;

private:
	std::string m_outlineColor;
};