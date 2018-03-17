#include "stdafx.h"
#include "../Task2_v5/htmldecode.h"

using namespace std;

TEST_CASE("FindAndReplace - find some text and replace all with other text")
{
	string str = "my name is Olga, but I like Olga not such as Julia";
	FindAndReplace(str, "Olga", "Ira");
	CHECK(str == "my name is Ira, but I like Ira not such as Julia");

	str = "OlgaIra";
	FindAndReplace(str, "Olga", "Ira");
	CHECK(str == "IraIra");

	str = "Ira";
	FindAndReplace(str, "Olga", "Ira");
	CHECK(str == "Ira");

	str = "Hello Olg";
	FindAndReplace(str, "Olga", "Ira");
	CHECK(str == "Hello Olg");

	str = "";
	FindAndReplace(str, "Olga", "Ira");
	CHECK(str == "");
	
	str = "Olga";
	FindAndReplace(str, "Olga", "");
	CHECK(str == "");
}

TEST_CASE("HtmlDecodeString - replace all in string")
{
	CHECK(HtmlDecodeString("&amp;&lt;&gt;&amp;&quot;&apos;") == "&<>&\"'");
	CHECK(HtmlDecodeString("") == "");
	CHECK(HtmlDecodeString("&amp;lt;") == "&lt;");
	CHECK(HtmlDecodeString("&amp") == "&amp");
}





