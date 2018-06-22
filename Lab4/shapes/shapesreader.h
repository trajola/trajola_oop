#pragma once
#include <memory>
#include <map>
#include <functional>
#include "shape.h"

class CShapesReader
{
public:
	CShapesReader(std::istream &input);
	std::shared_ptr<CShape> ReadShape() const;

private:
	std::shared_ptr<CShape> ReadLine(std::istream &args) const;
	std::shared_ptr<CShape> ReadCircle(std::istream &args) const;
	std::shared_ptr<CShape> ReadTriangle(std::istream &args) const;
	std::shared_ptr<CShape> ReadRectangle(std::istream &args) const;
	std::istream &m_input;
	using Actions = std::map<std::string, std::function<std::shared_ptr<CShape>(std::istream & args)>>;
	const Actions m_actions;
};
