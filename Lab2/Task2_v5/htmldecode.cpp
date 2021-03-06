
#include "stdafx.h"
#include "htmldecode.h"
#include "getlineiterator.h"

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>

void FindAndReplace(std::string & subject, std::string const & search, std::string const & replace)
{
	if (search.empty())
		return;
	size_t pos = 0;
	std::string resultStr;
	while (pos < subject.length()) 
	{
		auto foundPos = subject.find(search, pos);
		resultStr.append(subject, pos, foundPos - pos);
		pos = foundPos;
		if (foundPos != std::string::npos)
		{
			resultStr.append(replace);
			pos += search.length();
		}
	}
	subject = move(resultStr);
}

PairsSearchReplace const replacement[] =
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
	std::transform(CGetlineIterator(input), CGetlineIterator(),
		std::ostream_iterator<std::string>(output, "\n"), transformer);
	return input.good();
}


