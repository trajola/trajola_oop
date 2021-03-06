#include "stdafx.h"
#include "../Task2_v5/htmldecode.h"

using namespace std;

TEST_CASE("FindAndReplace - find some text and replace all with other text")
{
	string str;

	str = "";
	FindAndReplace(str, "", "");
	CHECK(str == "");

	str = "Olga";
	FindAndReplace(str, "Olga", "");
	CHECK(str == "");

	str = "Ira";
	FindAndReplace(str, "", "");
	CHECK(str == "Ira");

	str = "Olga";
	FindAndReplace(str, "", "Olga");
	CHECK(str == "Olga");

	str = "";
	FindAndReplace(str, "Olga", "Ira");
	CHECK(str == "");

	str = "OlgaIra";
	FindAndReplace(str, "Olga", "Ira");
	CHECK(str == "IraIra");

	str = "Ira";
	FindAndReplace(str, "Olga", "Ira");
	CHECK(str == "Ira");

	str = "my name is Olga, but I like Olga not so much as Julia";
	FindAndReplace(str, "Olga", "Ira");
	CHECK(str == "my name is Ira, but I like Ira not so much as Julia");
	
}

TEST_CASE("HtmlDecodeString - replace all in string")
{
	CHECK(HtmlDecodeString("&amp;&lt;&gt;&amp;&quot;&apos;") == "&<>&\"'");
	CHECK(HtmlDecodeString("") == "");
	CHECK(HtmlDecodeString("&amp;lt;") == "&lt;");
	CHECK(HtmlDecodeString("&amp;   &amp;") == "&   &");
	CHECK(HtmlDecodeString("&amp;   &amp;\n&gt;   &lt;") == "&   &\n>   <");
	CHECK(HtmlDecodeString("some text\nand another text") == "some text\nand another text");
}





