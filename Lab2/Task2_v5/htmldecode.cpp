// Task2_v5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct pairsSearchReplace
{
	string search, replace;
};

vector<pairsSearchReplace> replacement = 
{
	{"&lt;", "<"}, {"&gt;", ">"}
};


void FindAndReplace(string & subject, string const & search, string const & replace)
{
	auto pos = subject.find(search);
	while (pos != string::npos) 
	{
		subject.replace(pos, search.length(), replace);
		pos = subject.find(search);
	}
}

string HtmlDecodeString(string const & strIn)
{
	string strOut = strIn;
	for (auto pair : replacement)
	{
		FindAndReplace(strOut, pair.search, pair.replace);
	}
	return strOut;
}

void HtmlDecodeText(istream & input, ostream & output)
{
	string strIn;
	while (getline(input , strIn))
	{ 
		string strOut = HtmlDecodeString(strIn);
		output << strOut << endl;
	}
}

int main()
{
	HtmlDecodeText(cin, cout);

	return 0;
}

