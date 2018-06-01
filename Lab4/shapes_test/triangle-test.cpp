// triangle-test.cpp : tests

#include "stdafx.h"
#include "../shapes/triangle.h"

TEST_CASE("Triangle has its points, black outlinecolor and white fillcolor by default")
{
	CTriangle triangle({ 0, 0 }, { 1, 1 }, { 0, 1 });
	CHECK(triangle.GetVertex1().x == 0);
	CHECK(triangle.GetVertex1().y == 0);
	CHECK(triangle.GetVertex2().x == 1);
	CHECK(triangle.GetVertex2().y == 1);
	CHECK(triangle.GetVertex3().x == 0);
	CHECK(triangle.GetVertex3().y == 1);
	CHECK(triangle.GetOutlineColor() == "#000000");
	CHECK(triangle.GetFillColor() == "#FFFFFF");
}

TEST_CASE("Triangle has its points, outlinecolor and fillcolor")
{
	CTriangle triangle({ 0, 0 }, { -1, -1 }, { 0, 1 }, "#00FF00", "#FF0000");
	CHECK(triangle.GetVertex1().x == 0);
	CHECK(triangle.GetVertex1().y == 0);
	CHECK(triangle.GetVertex2().x == -1);
	CHECK(triangle.GetVertex2().y == -1);
	CHECK(triangle.GetVertex3().x == 0);
	CHECK(triangle.GetVertex3().y == 1);
	CHECK(triangle.GetOutlineColor() == "#00FF00");
	CHECK(triangle.GetFillColor() == "#FF0000");
}

TEST_CASE("Triangle has correct perimeter and area")
{
	CTriangle triangle({ 0, 0 }, { 3, 0 }, { 0, 4 });
	CHECK(triangle.GetPerimeter() == 12.0);
	CHECK(triangle.GetArea() == 6.0);
}

TEST_CASE("Triangle has text representation")
{
	CTriangle triangle({ 0, 0 }, { 3, 0 }, { 0, 4 }, "#090909", "#FF00FF");
	CHECK(triangle.ToString() == R"(Triangle:
Vertex1 = (0.000, 0.000)
Vertex2 = (3.000, 0.000)
Vertex3 = (0.000, 4.000)
Perimeter = 12.000
Area = 6.000
OutlineColor = #090909
FillColor = #FF00FF
)");
}
