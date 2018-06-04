#include "stdafx.h"
#include <sstream>
#include "../shapes/readershapes.h"

void VerifyCommandHandling(const std::string &command, const std::string &expectedOutput)
{
	std::stringstream input;
	input = std::stringstream();
	CReaderShapes readShape(input);
	std::shared_ptr<IShape> shape;

	CHECK(input << command);
	shape = readShape.ExecuteCommand();
	CHECK(shape->ToString() == expectedOutput);
}

void ExpectOperationFailure(const std::string &command)
{
	std::stringstream input;
	input = std::stringstream();
	CReaderShapes createShape(input);
	std::shared_ptr<IShape> shape;

	CHECK(input << command);
	shape = createShape.ExecuteCommand();
	CHECK(!shape);
}


TEST_CASE("can create linesegment with color") 
{
	VerifyCommandHandling("line 1.0 0 3.5 0 #FF0000",
		R"(LineSegment:
StartPoint = (1.000, 0.000)
EndPoint = (3.500, 0.000)
Perimeter = 2.500
Area = 0.000
OutlineColor = #FF0000
)");
};


TEST_CASE("can create linesegment with default color")
{
	VerifyCommandHandling("line 1.0 0 3.5 0",
		R"(LineSegment:
StartPoint = (1.000, 0.000)
EndPoint = (3.500, 0.000)
Perimeter = 2.500
Area = 0.000
OutlineColor = #000000
)");
};

TEST_CASE("can create a circle with color")
{
	VerifyCommandHandling("circle 0.5 0.5 1 #FF0000 #00FF00",
		R"(Circle:
Center = (0.500, 0.500)
Radius = 1.000
Perimeter = 6.283
Area = 3.142
OutlineColor = #FF0000
FillColor = #00FF00
)");
};


TEST_CASE("can create a circle with default color")
{
	VerifyCommandHandling("circle 0.5 0.5 1",
		R"(Circle:
Center = (0.500, 0.500)
Radius = 1.000
Perimeter = 6.283
Area = 3.142
OutlineColor = #000000
FillColor = #FFFFFF
)");
};

TEST_CASE("can create a triangle with color")
{
	VerifyCommandHandling("triangle 0 0 2.5 2.5 2 0 #FF0000 #0000FF",
R"(Triangle:
Vertex1 = (0.000, 0.000)
Vertex2 = (2.500, 2.500)
Vertex3 = (2.000, 0.000)
Perimeter = 8.085
Area = 2.500
OutlineColor = #FF0000
FillColor = #0000FF
)");
};

TEST_CASE("can create a triangle with default color")
{
	VerifyCommandHandling("triangle 0 0 2.5 2.5 2 0",
		R"(Triangle:
Vertex1 = (0.000, 0.000)
Vertex2 = (2.500, 2.500)
Vertex3 = (2.000, 0.000)
Perimeter = 8.085
Area = 2.500
OutlineColor = #000000
FillColor = #FFFFFF
)");
};

TEST_CASE("can't do anything with incorrect parameters")
{
	ExpectOperationFailure("circle 1 5 d");
	ExpectOperationFailure("triangle");
	ExpectOperationFailure("line a a");
	ExpectOperationFailure("some unknown 0 0 1");
};

