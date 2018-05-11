
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

TEST_CASE("Check reading and writing to files")
{
	Dictionary dict1;
	CHECK(ReadDictionaryFromFile(dict1, "not-exist-file.txt") == false);
	CHECK(ReadDictionaryFromFile(dict1, "dict1.txt") == true);
	Dictionary dict2;
	dict2.emplace("meat", "мясо");
	dict2.emplace("cat", "кошка");
	CHECK(DictionariesAreEqual(dict1, dict2));
	CHECK(SaveDictionaryToFile(dict2, "dict2.txt") == true);
	CHECK(SaveDictionaryToFile(dict2, "not-exist/dict1.txt") == false);
}

TEST_CASE("Check getting translation")
{
	Dictionary dict;
	dict.emplace("meat", "мясо");
	dict.emplace("cat", "кошка");
	std::string translation;
	CHECK(Translate("cat", translation, dict) == true);
	CHECK(translation == "кошка");
	CHECK(Translate("kitty", translation, dict) == false);
}

