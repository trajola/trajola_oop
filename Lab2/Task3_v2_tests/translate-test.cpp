
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
	//сбрасываем флаги потока, начинаем чтение с начала
	inStrm.clear();
	inStrm.seekg(0);
	dict.emplace("meat", "мясо");
	CHECK(DictionariesAreEqual(ReadDictionaryFromStream(inStrm), dict));

	inStrm.str("meat\nмясо\ncat\nкошка\n");
	//сбрасываем флаги потока, начинаем чтение с начала
	inStrm.clear();
	inStrm.seekg(0);
	dict.emplace("meat", "мясо");
	dict.emplace("cat", "кошка");
	CHECK(DictionariesAreEqual(ReadDictionaryFromStream(inStrm), dict));
}

TEST_CASE("Check writing dictionary to stream")
{
	Dictionary dict;
	std::ostringstream outStrm, checkStrm("");
	WriteDictionaryToStream(dict, outStrm);
	CHECK(outStrm.str() == checkStrm.str());

	dict.emplace("meat", "мясо");
	checkStrm.str("meat\nмясо\n");
	outStrm.str("");
	WriteDictionaryToStream(dict, outStrm);
	CHECK(outStrm.str() == checkStrm.str());

	dict.emplace("cat", "кошка");
	checkStrm.str("cat\nкошка\nmeat\nмясо\n");
	outStrm.str("");
	WriteDictionaryToStream(dict, outStrm);
	CHECK(outStrm.str() == checkStrm.str());
}
