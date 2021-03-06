#include "stdafx.h"
#include "../myarray/myarray.h"
#include <string>
#include <sstream>
#include <algorithm>

TEST_CASE("After creation of array its size = 0, capacity = 0")
{
	CMyArray<int> array1;
	CHECK(array1.GetSize() == 0);
	CHECK(array1.GetCapacity() == 0);

	CMyArray<double> array2;
	CHECK(array2.GetSize() == 0);
	CHECK(array2.GetCapacity() == 0);

	CMyArray<std::string> array3;
	CHECK(array3.GetSize() == 0);
	CHECK(array3.GetCapacity() == 0);
}

using namespace std;

struct ArrayItem
{
	ArrayItem(int value = 0) : value(value)
	{}
	int value;
};

TEST_CASE("Can append elements to array and use [] with correct number to access elements")
{
	CMyArray<ArrayItem> array;
	
	array.Append(ArrayItem());
	CHECK(array.GetSize() == 1);
	CHECK(array.GetCapacity() == 1);
	CHECK(array[0].value == 0);

	array.Append(ArrayItem(5));
	CHECK(array.GetSize() == 2);
	CHECK(array.GetCapacity() == 2);
	CHECK(array[1].value == 5);

	array.Append(ArrayItem(10));
	CHECK(array.GetSize() == 3);
	CHECK(array.GetCapacity() == 4);
	CHECK(array[2].value == 10);
}

TEST_CASE("Can change element with []")
{
	CMyArray<ArrayItem> array;
	for (int i = 0; i < 10; i++)
		array.Append(ArrayItem(i));
	ArrayItem item(20);
	array[5] = item;
	CHECK(array[5].value == 20);
}

TEST_CASE("Get exception when [] is out of range")
{
	CMyArray<ArrayItem> array;
	CHECK_THROWS_AS(array[0], std::out_of_range);

	array.Append(ArrayItem(5));
	CHECK_THROWS_AS(array[1], std::out_of_range);
}

TEST_CASE("Can change size")
{
	CMyArray<ArrayItem> array;
	for (int i = 0; i < 10; i++)
		array.Append(ArrayItem(i));
	
	array.Resize(5);
	CHECK(array.GetSize() == 5);
	CHECK(array.GetCapacity() == 16);
	CHECK(array[4].value == 4);
	CHECK_THROWS_AS(array[5], std::out_of_range);

	array.Resize(17);
	CHECK(array.GetSize() == 17);
	CHECK(array.GetCapacity() == 32);
	CHECK(array[16].value == 0);
	CHECK_THROWS_AS(array[17], std::out_of_range);
}

TEST_CASE("Can clear elements")
{
	CMyArray<ArrayItem> array;
	for (int i = 0; i < 10; i++)
		array.Append(ArrayItem(i));

	array.Clear();
	CHECK(array.GetSize() == 0);
	CHECK(array.GetCapacity() == 16);
	CHECK_THROWS_AS(array[0], std::out_of_range);
}

TEST_CASE("Can copy array with copy constructor")
{
	CMyArray<ArrayItem> array1;
	for (int i = 0; i < 3; i++)
		array1.Append(ArrayItem(i));

	CMyArray<ArrayItem> array2(array1);
	CHECK(array1.GetSize() == array2.GetSize());
	CHECK(array1[0].value == array2[0].value);
	CHECK(array1[1].value == array2[1].value);
	CHECK(array1[2].value == array2[2].value);
}

TEST_CASE("Can move array with move constructor")
{
	CMyArray<ArrayItem> array1;
	for (int i = 0; i < 3; i++)
		array1.Append(ArrayItem(i));

	CMyArray<ArrayItem> array2(std::move(array1));
	CHECK(array1.GetSize() == 0);
	CHECK(array2.GetSize() == 3);
	CHECK(array2[0].value == 0);
	CHECK(array2[1].value == 1);
	CHECK(array2[2].value == 2);
}

TEST_CASE("Can copy array with =")
{
	CMyArray<ArrayItem> array1;
	for (int i = 0; i < 3; i++)
		array1.Append(ArrayItem(i));

	CMyArray<ArrayItem> array2 = array1;
	CHECK(array1.GetSize() == array2.GetSize());
	CHECK(array1[0].value == array2[0].value);
	CHECK(array1[1].value == array2[1].value);
	CHECK(array1[2].value == array2[2].value);
}


TEST_CASE("Can use iterator, operations ++, <")
{
	CMyArray<ArrayItem> array;
	for (int i = 0; i < 3; i++)
		array.Append(ArrayItem(i));

	for (auto i = array.begin(); i < array.end(); ++i)
	{
		CHECK( i->value == i - array.begin());
		CHECK((*i).value == i[0].value);
	}

	std::ostringstream out;
	for (auto const & item : array)
	{
		out << item.value << " ";
	}
	CHECK(out.str() == "0 1 2 ");
}

TEST_CASE("Can use reverse iterator, operations ++, <")
{
	CMyArray<ArrayItem> array;
	for (int i = 0; i < 3; i++)
		array.Append(ArrayItem(i));

	std::ostringstream out;
	for (auto i = array.rbegin(); i < array.rend(); ++i)
	{
		out << i->value << " ";
	}
	CHECK(out.str() == "2 1 0 ");
}

TEST_CASE("Can use sort algorithm")
{
	CMyArray<int> array;
	array.Append(3);
	array.Append(1);
	array.Append(2);

	std::sort(array.begin(), array.end());

	std::ostringstream out;
	for (auto i = array.begin(); i < array.end(); ++i)
	{
		out << *i << " ";
	}
	CHECK(out.str() == "1 2 3 ");
}

TEST_CASE("operations with iterator are correct")
{
	CMyArray<ArrayItem> array;
	for (int i = 0; i < 3; i++)
		array.Append(ArrayItem(i));

	CHECK((array.begin() + 2)->value == 2);
	CHECK((array.end() - 2)->value == 1);

	CHECK((array.begin() + 1) == (array.end() - 2));
	CHECK(((array.begin() + 1) == array.end()) == false);

	CHECK(array.begin() != array.end());
	CHECK(((array.begin() + 1) != (array.end() - 2)) == false);

	CHECK(array.begin() < array.end());
	CHECK((array.begin() > array.end()) == false);
	CHECK((array.begin() >= array.end()) == false);

	CHECK(array.end() > array.begin());
	CHECK((array.end() <= array.begin()) == false);
	CHECK((array.end() < array.begin()) == false);

	CHECK((array.begin() + 1) <= (array.end() - 1));
	CHECK((array.end() - 2) >= (array.begin() + 1));
	CHECK(array.begin() <= array.end());
	CHECK(array.end() >= array.begin());
}
