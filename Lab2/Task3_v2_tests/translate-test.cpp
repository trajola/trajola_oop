
#include "stdafx.h"
#include "../Task3_v2/translate.h"
#include <sstream>

bool DictionariesAreEqual(Dictionary const& x, Dictionary const& y)
{
	return x == y;
}

TEST_CASE("Check reading dictionary from stream")
{
	std::istringstream inStrm("");
	Dictionary dict;
	CHECK(DictionariesAreEqual(ReadDictionaryFromStream(inStrm), dict));

	inStrm.str("meat\nмясо");
	inStrm.clear();
	inStrm.seekg(0);
	Dictionary dictRead = ReadDictionaryFromStream(inStrm);
	dict.insert(std::pair<std::string, std::string>("meat", "мясо"));
	CHECK(DictionariesAreEqual(dictRead, dict));
}