// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "shape.h"
#include "shapesreader.h"
#include "canvas-svg.h"

void Info(const std::vector<std::shared_ptr<CShape>> &shapes)
{
	for (const auto & shape : shapes)
	{
		std::cout << shape->ToString() << std::endl;
	}
}

void DrawToFile(const std::vector<std::shared_ptr<CShape>> &shapes, std::string const & fileName)
{
	CCanvas canvas(fileName);
	for (const auto & shape : shapes)
	{
		shape->Draw(canvas);
	}
}

std::shared_ptr<CShape> FindShapeWithMaxArea(const std::vector<std::shared_ptr<CShape>> & shapes)
{
	if (shapes.empty())
		return nullptr;
	auto max = std::max_element(shapes.begin(), shapes.end(), 
		[](auto&& shape1, auto&& shape2) {
		return (shape1->GetArea() < shape2->GetArea());
	});
	return *max;
}

std::shared_ptr<CShape> FindShapeWithMinPerimeter(const std::vector<std::shared_ptr<CShape>> & shapes)
{
	if (shapes.empty())
		return nullptr;
	auto min = std::min_element(shapes.begin(), shapes.end(),
		[](auto&& shape1, auto&& shape2) {
		return (shape1->GetPerimeter() < shape2->GetPerimeter());
	});
	return *min;
}

int main()
{
	std::vector<std::shared_ptr<CShape>> shapes;
	std::ifstream input("input.txt");
	CShapesReader shapeReader(input);

	while (auto shape = shapeReader.ReadShape())
	{
		shapes.push_back(shape);	
	}

	Info(shapes);
	
	auto shapeWithMaxArea = FindShapeWithMaxArea(shapes);
	if (shapeWithMaxArea)
	{
		std::cout << "Shape with MAX area:\n" << shapeWithMaxArea->ToString() << "\n";
	}

	auto shapeWithMinPerimeter = FindShapeWithMinPerimeter(shapes);
	if (shapeWithMinPerimeter)
	{
		std::cout << "Shape with MIN perimeter:\n" << shapeWithMinPerimeter->ToString() << "\n";
	}

	DrawToFile(shapes, "picture.svg");

	return 0;
}