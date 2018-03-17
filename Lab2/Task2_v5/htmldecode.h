#pragma once
#include <string>
#include <iostream>
#include <functional>

struct PairsSearchReplace
{
	std::string search, replace;
};

void FindAndReplace(std::string & subject, std::string const & search, std::string const & replace);

std::string HtmlDecodeString(std::string const & strIn);

bool HtmlDecodeText(std::istream & input, std::ostream & output, const std::function<std::string(std::string)>& transformer);
