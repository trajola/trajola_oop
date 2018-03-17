// Task2_v5.cpp : Defines the entry point for the console application.
// декодируем текст, содержащий html закодированные символы

#include "stdafx.h"
#include "htmldecode.h"

int main()
{
	HtmlDecodeText(std::cin, std::cout, &HtmlDecodeString);
	return 0;
}