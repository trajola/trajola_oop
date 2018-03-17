
#include "stdafx.h"
#include "htmldecode.h"

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>

void FindAndReplace(std::string & subject, std::string const & search, std::string const & replace)
{
	auto pos = subject.find(search);
	while (pos != std::string::npos) 
	{
		subject.replace(pos, search.length(), replace);
		pos = subject.find(search);
	}
}

PairsSearchReplace replacement[] =
{
	{ "&lt;", "<" },{ "&gt;", ">" },{ "&quot;" , "\"" },{ "&apos;" , "'" },{ "&amp;" , "&" }
};

std::string HtmlDecodeString(std::string const & strIn)
{
	std::string strOut = strIn;
	for (auto pair : replacement)
	{
		FindAndReplace(strOut, pair.search, pair.replace);
	}
	return strOut;
}

bool HtmlDecodeText(std::istream & input, std::ostream & output, const std::function<std::string(std::string)>& transformer)
{
	std::transform(std::istream_iterator<std::string>(input), std::istream_iterator<std::string>(),
		std::ostream_iterator<std::string>(output), transformer);
	return input.good();
}


