// Task1_v6.cpp : Defines the entry point for the console application.
//Lab 2, task 1, variant 6
//�������� ������ ������� ������� �� ������������ ������� ��������� �������
//� ��������� �� ����������� ������� ��������� �������

#include "stdafx.h"

int main()
{
	DoubleArray numbers = GetArrayFromCin();
	MultToMaxAndDivideToMin(numbers);
	std::sort(numbers.begin(), numbers.end());
	PrintArrayToCout(numbers);

	return 0;
}
