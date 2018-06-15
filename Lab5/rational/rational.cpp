#pragma once
#include "stdafx.h"
#include "rational.h"
#include <numeric>

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (m_denominator == 0)
		throw std::invalid_argument("The denominator can not be zero");

	if (m_denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}

	int gcd = std::gcd(m_numerator, m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return static_cast<double>(m_numerator) / m_denominator;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	return std::pair<int, CRational>(m_numerator / m_denominator, CRational(m_numerator % m_denominator, m_denominator));
}

CRational const CRational::operator -() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational const CRational::operator +() const
{
	return *this;
}

CRational const operator +(CRational const & number1, CRational const & number2)
{
	int denominator = std::lcm(number1.GetDenominator(), number2.GetDenominator());
	int numerator = number1.GetNumerator() * (denominator / number1.GetDenominator()) + number2.GetNumerator() * (denominator / number2.GetDenominator());
	return CRational(numerator, denominator);
}

CRational const operator -(CRational const & number1, CRational const & number2)
{
	return number1 + (-number2);
}

CRational & CRational::operator +=(CRational const &number)
{
	return *this = *this + number;
}

CRational & CRational::operator -=(CRational const &number)
{
	return *this = *this - number;
}

CRational const operator *(CRational const & number1, CRational const & number2)
{
	return CRational(number1.GetNumerator() * number2.GetNumerator(), number1.GetDenominator() * number2.GetDenominator());
}

CRational const operator /(CRational const & number1, CRational const & number2)
{
	return CRational(number1.GetNumerator() * number2.GetDenominator(), number1.GetDenominator() * number2.GetNumerator());
}

CRational & CRational::operator *=(CRational const & number)
{
	return *this = *this * number;
}

CRational & CRational::operator /=(CRational const & number)
{
	return *this = *this / number;
}

std::ostream & operator <<(std::ostream & strm, CRational const & number)
{
	strm << number.GetNumerator() << '/' << number.GetDenominator();
	return strm;
}


std::istream & operator >>(std::istream &strm, CRational &number)
{
	int numerator, denominator;
	if (strm >> numerator && strm.get() == '/' && strm >> denominator)
		number = CRational(numerator, denominator);
	return strm;
}

bool const operator ==(CRational const & number1, CRational const & number2)
{
	return number1.GetNumerator() == number2.GetNumerator() && number1.GetDenominator() == number2.GetDenominator();
}

bool const operator !=(CRational const & number1, CRational const & number2)
{
	return !(number1.GetNumerator() == number2.GetNumerator() && number1.GetDenominator() == number2.GetDenominator());
}

bool const operator <(CRational const & number1, CRational const & number2)
{
	int denominator = std::lcm(number1.GetDenominator(), number2.GetDenominator());
	return number1.GetNumerator() * (denominator * number1.GetDenominator()) < number2.GetNumerator() * (denominator * number2.GetDenominator());
}

bool const operator >(CRational const & number1, CRational const & number2)
{
	int denominator = std::lcm(number1.GetDenominator(), number2.GetDenominator());
	return number1.GetNumerator() * (denominator * number1.GetDenominator()) > number2.GetNumerator() * (denominator * number2.GetDenominator());

}

bool const operator <=(CRational const & number1, CRational const & number2)
{
	return number1 < number2 || number1 == number2;
}

bool const operator >=(CRational const & number1, CRational const & number2) 
{
	return number1 > number2 || number1 == number2;
}


