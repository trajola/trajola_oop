// circle-test.cpp : tests

#include "stdafx.h"
#include "../shapes/circle.h"
#define _USE_MATH_DEFINES
#include <math.h>

TEST_CASE("Circle has center and radius, black outlinecolor and white fillcolor by default")
{
	CCircle circle({ 10, 10 }, 4.5);
	CHECK(circle.GetCenter().x == 10);
	CHECK(circle.GetCenter().y == 10);
	CHECK(circle.GetRadius() == 4.5);
	CHECK(circle.GetOutlineColor() == "#000000");
	CHECK(circle.GetFillColor() == "#FFFFFF");
}

TEST_CASE("Circle has center and radius, outlinecolor and fillcolor")
{
	CCircle circle({ 10, 10 }, 4.5, "#00FF00", "#FF0000");
	CHECK(circle.GetCenter().x == 10);
	CHECK(circle.GetCenter().y == 10);
	CHECK(circle.GetRadius() == 4.5);
	CHECK(circle.GetOutlineColor() == "#00FF00");
	CHECK(circle.GetFillColor() == "#FF0000");
}

TEST_CASE("Circle has correct perimeter and area")
{
	CCircle circle({ 0, 0 }, 2, "#00FF00", "#FF0000");
	CHECK(circle.GetPerimeter() == 4 *M_PI);
	CHECK(circle.GetArea() == 4 * M_PI);
}

TEST_CASE("Circle has text representation")
{
	CCircle circle({ 0, 0 }, 2, "#0000AA", "#909090");
	CHECK(circle.ToString() == R"(Circle:
Center = (0.000, 0.000)
Radius = 2.000
Perimeter = 12.566
Area = 12.566
OutlineColor = #0000AA
FillColor = #909090
)");
}

