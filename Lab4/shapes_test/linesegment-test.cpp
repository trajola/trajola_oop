// segmentline-test.cpp : tests

#include "stdafx.h"
#include "../shapes/linesegment.h"

TEST_CASE("Linesegment has coordinates and black color by default")
{
	CLineSegment line({ 0, 0 }, { 3, -4.5 });
	CHECK(line.GetStartPoint().x == 0);
	CHECK(line.GetStartPoint().y == 0);
	CHECK(line.GetEndPoint().x == 3);
	CHECK(line.GetEndPoint().y == -4.5);
	CHECK(line.GetOutlineColor() == "#000000");
}

TEST_CASE("Linesegment has coordinates and color")
{
	CLineSegment line({ 0, 0 }, { 3, -4.5 }, "#00FF00");
	CHECK(line.GetStartPoint().x == 0);
	CHECK(line.GetStartPoint().y == 0);
	CHECK(line.GetEndPoint().x == 3);
	CHECK(line.GetEndPoint().y == -4.5);
	CHECK(line.GetOutlineColor() == "#00FF00");
}

TEST_CASE("Linesegment has valid color or black color if start color is wrong")
{
	CLineSegment line1({ 0, 0 }, { 3, -4.5 }, "#RTFF00");
	CHECK(line1.GetOutlineColor() == "#000000");
	CLineSegment line2({ 0, 0 }, { 3, -4.5 }, "#00FFF00");
	CHECK(line2.GetOutlineColor() == "#000000");
	CLineSegment line3({ 0, 0 }, { 3, -4.5 }, "#00ff00");
	CHECK(line3.GetOutlineColor() == "#00ff00");
}

TEST_CASE("Linesegment has perimeter and area = 0")
{
	CLineSegment line({ 0, 0 }, { 3, -4 });
	CHECK(line.GetPerimeter() == 5);
	CHECK(line.GetArea() == 0);
}

TEST_CASE("Linesegment has text representation")
{
	CLineSegment line({ 0, 0 }, { 3, -4 }, "#0000AA");
	CHECK(line.ToString() == R"(LineSegment:
StartPoint = (0.000, 0.000)
EndPoint = (3.000, -4.000)
Perimeter = 5.000
Area = 0.000
OutlineColor = #0000AA
)");
}

