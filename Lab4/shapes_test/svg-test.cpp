#include "stdafx.h"
#include "../shapes/canvas-svg.h"
#include "../shapes/linesegment.h"
#include "../shapes/circle.h"
#include "../shapes/triangle.h"
#include "../shapes/rectangle.h"

TEST_CASE("Can create svg file with Draw")
{
	CCanvas canvas("picture.svg");
	CLineSegment line({ 50, 90 }, { 50, 190 }, "#000000");
	line.Draw(canvas);
	CCircle circle({50, 50}, 40, "#000000", "#FF0000");
	circle.Draw(canvas);
	CTriangle triangle({150, 10}, {120, 100}, {180, 100}, "#000000", "#BBBB00");
	triangle.Draw(canvas);
	CRectangle rectangle({ 120, 100 }, {180, 250}, "#000000", "#B0B000");
	rectangle.Draw(canvas);
}

