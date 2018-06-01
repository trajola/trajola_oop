#pragma once
#include "stdafx.h"
#include "shape.h"

class CReaderShapes
{
public:
	CReaderShapes(std::istream &input);
	std::shared_ptr<IShape> ExecuteCommand() const;

private:
	std::shared_ptr<IShape> ReadLine(std::istream &args) const;
	std::shared_ptr<IShape> ReadCircle(std::istream &args) const;
	std::shared_ptr<IShape> ReadTriangle(std::istream &args) const;
	std::shared_ptr<IShape> ReadRectangle(std::istream &args) const;
	std::istream &m_input;
	typedef std::map<std::string, std::function<std::shared_ptr<IShape>(std::istream & args)>> Actions;
	const Actions m_actions;
};
