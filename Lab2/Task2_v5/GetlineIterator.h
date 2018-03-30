#pragma once
#include <iterator>
#include <string>

// ���������������� �������� ��� ����������� ���������� ����� �� �������� ������
// ��� ������ getline
// ��� ���������� ���������������� ���������� ������ istream_iterator
class CGetlineIterator : public std::iterator < std::input_iterator_tag, std::string >
{
public:
	// ������������ ��������, ��������������� � ������ ������ (m_strm == nullptr)
	CGetlineIterator() :m_strm(nullptr)
	{}

	// ������������ ��������, ��������������� � �������� �������
	CGetlineIterator(std::istream & strm)
		:m_strm(&strm)
	{
		GetNextLine();
	}

	// �������� ������� � ������
	const std::string& operator*()const
	{
		return m_str;
	}

	// �������� ��� ������� � ����� ��������
	const std::string* operator->()const
	{
		return &m_str;
	}

	// ���������� ����� ��������� ++
	CGetlineIterator & operator++()
	{
		GetNextLine();

		return *this; // �������� ++ ���������� ������ �� ��� ������
	}

	// ����������� ����� ��������� ++
	const CGetlineIterator operator++(int)
	{
		auto tmp(*this);
		++ *this;
		return tmp; // ������������ ������� �������� ���������
	}

	/*
	��������� ��������� ����������
	�������� �� ������������: http://www.cplusplus.com/reference/iterator/istream_iterator/operators/
		Two end-of-stream iterators are always equal (no matter the particular stream each is associated).
		Two non-end-of-stream iterators are equal when they are constructed from the same stream, or one is a copy of the other.
		An end-of-stream iterator is never equal to a non-end-of-stream iterator.
	*/
	bool operator==(const CGetlineIterator & rhs)const
	{
		return m_strm == rhs.m_strm;
	}
	bool operator!=(const CGetlineIterator & rhs)const
	{
		return !(*this == rhs);
	}
private:

	void GetNextLine()
	{
		if (m_strm && !std::getline(*m_strm, m_str))
		{
			// ����� ���������� ��� ��������� ������ - ���������� ���������
			m_strm = nullptr;
		}
	}

	std::istream * m_strm = nullptr;
	std::string m_str;
};

