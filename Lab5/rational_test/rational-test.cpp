#include "stdafx.h"
#include "../rational/rational.h"
#include <sstream>

void ExpectOperationSuccess(CRational const & number, int expectedNumerator, int expectedDenominator)
{
	CHECK(number.GetNumerator() == expectedNumerator);
	CHECK(number.GetDenominator() == expectedDenominator);
}

TEST_CASE("can create rational 0 by default")
{
	ExpectOperationSuccess(CRational(), 0, 1);
}

TEST_CASE("can create rational from value by default")
{
	ExpectOperationSuccess(CRational(5, 1), 5, 1);
	ExpectOperationSuccess(CRational(-5, 1), -5, 1);
}

TEST_CASE("create rationals with numerator and denominator")
{
	ExpectOperationSuccess(CRational(-5, 3), -5, 3);
	ExpectOperationSuccess(CRational(5, -3), -5, 3);
	ExpectOperationSuccess(CRational(5, 3), 5, 3);
	ExpectOperationSuccess(CRational(-5, -3), 5, 3);
}

TEST_CASE("numerator and denominator are normalized")
{
	ExpectOperationSuccess(CRational(10, 5), 2, 1);
	ExpectOperationSuccess(CRational(-5, 10), -1, 2);
	ExpectOperationSuccess(CRational(0, 2), 0, 1);
}

TEST_CASE("can't create rational with denominator 0")
{
	CHECK_THROWS_AS(CRational(1, 0), std::invalid_argument);
}

TEST_CASE("can convert rational to double")
{
	CHECK(CRational(1, 2).ToDouble() == 0.5);
	CHECK(CRational(-5, 20).ToDouble() == -0.25);
	CHECK(CRational(0, 40).ToDouble() == 0.0);
}

TEST_CASE("can convert rational to compond")
{
	CHECK(CRational(3, 2).ToCompoundFraction() == std::pair<int, CRational>(1, CRational(1, 2)));
	CHECK(CRational(-3, 2).ToCompoundFraction() == std::pair<int, CRational>(-1, CRational(-1, 2)));
	CHECK(CRational(1, 2).ToCompoundFraction() == std::pair<int, CRational>(0, CRational(1, 2)));
	CHECK(CRational(3, 3).ToCompoundFraction() == std::pair<int, CRational>(1, CRational(0, 1)));
	CHECK(CRational(0, 2).ToCompoundFraction() == std::pair<int, CRational>(0, CRational(0, 1)));
}

TEST_CASE("can use unary + operation")
{
	ExpectOperationSuccess(+CRational(5, 3), 5, 3);
	ExpectOperationSuccess(+CRational(-5, 3), -5, 3);
}

TEST_CASE("can use unary - operation")
{
	ExpectOperationSuccess(-CRational(5, 3), -5, 3);
	ExpectOperationSuccess(-CRational(-5, 3), 5, 3);
}

TEST_CASE("can use binary + operation")
{
	ExpectOperationSuccess(CRational(5, 3) + CRational(3, 5), 34, 15);
	ExpectOperationSuccess(CRational(1, 2) + CRational(1, 2), 1, 1);
	ExpectOperationSuccess(CRational(1, 2) + CRational(-1, 4), 1, 4);
	ExpectOperationSuccess(CRational(5, 3) + 2, 11, 3);
	ExpectOperationSuccess(2 + CRational(-5, 3), 1, 3);
}

TEST_CASE("can use binary - operation")
{
	ExpectOperationSuccess(CRational(5, 3) - CRational(2, 5), 19, 15);
	ExpectOperationSuccess(CRational(2, 9) - CRational(8, 9), -2, 3);
	ExpectOperationSuccess(CRational(8, 9) - CRational(-1, 9), 1, 1);
	ExpectOperationSuccess(CRational(5, 3) - 2, -1, 3);
	ExpectOperationSuccess(2 - CRational(3, 5), 7, 5);
}

TEST_CASE("can use += operation")
{
	ExpectOperationSuccess(CRational(1, 2) += CRational(1, 4), 3, 4);
	ExpectOperationSuccess(CRational(1, 2) += CRational(-1, 2), 0, 1);
	ExpectOperationSuccess(CRational(1, 2) += CRational(3, 2), 2, 1);
	ExpectOperationSuccess(CRational(1, 2) += 1, 3, 2);
}

TEST_CASE("can use -= operation")
{
	ExpectOperationSuccess(CRational(3, 2) -= CRational(2, 4), 1, 1);
	ExpectOperationSuccess(CRational(1, 2) -= CRational(-1, 2), 1, 1);
	ExpectOperationSuccess(CRational(5, 2) -= CRational(1, 2), 2, 1);
	ExpectOperationSuccess(CRational(1, 2) -= 1, -1, 2);
}

TEST_CASE("can use binary * operation")
{
	ExpectOperationSuccess(CRational(5, 3) * CRational(3, 5), 1, 1);
	ExpectOperationSuccess(CRational(5, 3) * CRational(-6, 20), -1, 2);
}

TEST_CASE("can use binary / operation")
{
	ExpectOperationSuccess(CRational(5, 3) / CRational(5, 3), 1, 1);
	ExpectOperationSuccess(CRational(5, 3) / CRational(-5, 3), -1, 1);
	CHECK_THROWS_AS(CRational(1) / CRational(), std::invalid_argument);
}

TEST_CASE("can use *= operation")
{
	ExpectOperationSuccess(CRational(5, 3) *= CRational(3, 5), 1, 1);
	ExpectOperationSuccess(CRational(4, 5) *= CRational(3, 4), 3, 5);
	ExpectOperationSuccess(CRational(4, 5) *= -2, -8, 5);
}

TEST_CASE("can use /= operation")
{
	ExpectOperationSuccess(CRational(5, 3) /= CRational(5), 1, 3);
	ExpectOperationSuccess(CRational(15, 8) /= CRational(-3, 2), -5, 4);
	ExpectOperationSuccess(CRational(5, 3) /= -5, -1, 3);
	CHECK_THROWS_AS(CRational(1) /= CRational(), std::invalid_argument);
}

TEST_CASE("can check == ")
{
	CHECK(CRational(10, 2) == CRational(5, 1));
	CHECK(CRational(5, -3) == CRational(-5, 3));
	CHECK(CRational(5, 3) == CRational(-5, -3));
	CHECK(CRational(5, 5) == 1);
	CHECK((CRational(5, 5) == CRational(5, 3)) == false);
	CHECK((CRational(5, 5) == CRational(5, -5)) == false);
	CHECK((2 == CRational(5, 5)) == false);
}

TEST_CASE("can check != ")
{
	CHECK(CRational(5, 3) != CRational(5, -3));
	CHECK(CRational(5, 3) != CRational(5, 2));
	CHECK(CRational(5, 3) != CRational(-5, 3));
	CHECK(2 != CRational(5, 5));
	CHECK((CRational(5, 3) != CRational(5, 3)) == false);
	CHECK((CRational(15, 9) != CRational(5, 3)) == false);
	CHECK((CRational(5, 5) != 1) == false);
}

TEST_CASE("can check < > <= >= ")
{
	CHECK(CRational(5, 3) > CRational(4, 3));
	CHECK((CRational(5, 3) < CRational(4, 3)) == false);

	CHECK(CRational(5, 3) > CRational(-4, 3));
	CHECK((CRational(5, 3) < CRational(-4, 3)) == false);

	CHECK(CRational(4, 3) < CRational(5, 6));
	CHECK((CRational(4, 3) > CRational(5, 6)) == false);

	CHECK((CRational(5, 5) > CRational(5, 5)) == false);
	CHECK((CRational(5, 5) < CRational(5, 5)) == false);
	CHECK(CRational(5, 5) >= CRational(5, 5));
	CHECK(CRational(5, 5) <= CRational(5, 5));

	CHECK(CRational(5, 10) > 0);
	CHECK(CRational(-5, 10) < 0);
	CHECK(CRational() >= 0);
	CHECK(CRational() <= 0);
	CHECK((CRational() > 0) == false);
	CHECK((CRational() < 0) == false);
}

TEST_CASE("can use operator << ")
{
	std::ostringstream outStr;
	outStr << CRational(-1, 3);
	CHECK(outStr.str() == "-1/3");
}

TEST_CASE("can use operator >>")
{
	std::istringstream inStr;
	inStr.str("3/5");
	CRational number;
	inStr >> number;
	CHECK(number == CRational(3, 5));
}




