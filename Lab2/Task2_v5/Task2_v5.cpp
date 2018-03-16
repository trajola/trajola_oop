// Task2_v5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

void FindAndReplace(string & subject, string const & search, string const & replace)
{
	auto pos = subject.find(search);
	while (pos != string::npos) 
	{
		subject.replace(pos, search.length(), replace);
		pos = subject.find(search);
	}
}

string HtmlDecode(const string & strIn)
{
	string strOut = strIn;
	FindAndReplace(strOut, "&lt;", "<");
	FindAndReplace(strOut, "&gt;", ">");
		
	return strOut;
}

int main()
{
	string strIn, strOut;
	getline(cin, strIn);
	strOut = HtmlDecode(strIn);
	cout << strOut << endl;

	
	return 0;
}

