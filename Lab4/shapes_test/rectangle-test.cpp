// rectangle-test.cpp : tests

#include "stdafx.h"
#include "../shapes/rectangle.h"

TEST_CASE("Rectangle has its points, black outlinecolor and white fillcolor by default")
{
	CRectangle rectangle({ 0, 1 }, { 1, 0 });
	CHECK(rectangle.GetLeftTop().x == 0);
	CHECK(rectangle.GetLeftTop().y == 0);
	CHECK(rectangle.GetRightBottom().x == 1);
	CHECK(rectangle.GetRightBottom().y == 1);
	CHECK(rectangle.GetOutlineColor() == "#000000");
	CHECK(rectangle.GetFillColor() == "#FFFFFF");
}

TEST_CASE("Rectangle has its points, outlinecolor and fillcolor")
{
	CRectangle rectangle({ 1, 0 }, { 0, 1 }, "#FF00FF", "#00FF00");
	CHECK(rectangle.GetLeftTop().x == 0);
	CHECK(rectangle.GetLeftTop().y == 0);
	CHECK(rectangle.GetRightBottom().x == 1);
	CHECK(rectangle.GetRightBottom().y == 1);
	CHECK(rectangle.GetOutlineColor() == "#FF00FF");
	CHECK(rectangle.GetFillColor() == "#00FF00");
}

TEST_CASE("Rectangle has correct perimeter and area")
{
	CRectangle rectangle({ 1, 0 }, { 0, 1 });
	CHECK(rectangle.GetPerimeter() == 4.0);
	CHECK(rectangle.GetArea() == 1.0);
}

TEST_CASE("Rectangle has text representation")
{
	CRectangle rectangle({ 1, 0 }, { 0, 1 }, "#090909", "#FF00FF");
	CHECK(rectangle.ToString() == R"(Rectangle:
LeftTop = (0.000, 0.000)
RightBottom = (1.000, 1.000)
Perimeter = 4.000
Area = 1.000
OutlineColor = #090909
FillColor = #FF00FF
)");
}
