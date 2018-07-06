#pragma once
#include <assert.h>

template <typename T>
class CMyIterator
{
	template <typename T> friend class CMyArray;

private:
	CMyIterator(T* p = nullptr) noexcept
		: m_pointer(p)
	{
	}

	T * m_pointer = nullptr;

public:
	using iterator_category = std::random_access_iterator_tag;
	using self_type = CMyIterator;
	using value_type = T;
	using reference = T & ;
	using pointer = T * ;
	using difference_type = ptrdiff_t;

	CMyIterator() noexcept
		: m_pointer(nullptr)
	{
	}

	CMyIterator& operator--() noexcept
	{
		assert(--m_pointer);
		return *this;
	}

	CMyIterator& operator+=(int const &number) noexcept
	{
		assert(m_pointer += number);
		return *this;
	}

	CMyIterator& operator-=(int const &number) noexcept
	{
		assert(m_pointer -= number);
		return *this;
	}

	CMyIterator const operator--(int) noexcept
	{
		CMyIterator temp(*this);
		assert(--m_pointer);
		return temp;
	}

	CMyIterator& operator++() noexcept
	{
		assert(++m_pointer);
		return *this;
	}

	CMyIterator const operator++(int) noexcept
	{
		CMyIterator temp(*this);
		assert(++m_pointer);
		return temp;
	}

	bool operator<(CMyIterator const &other) const noexcept
	{
		return m_pointer < other.m_pointer;
	}

	bool operator>(CMyIterator const &other) const noexcept
	{
		return m_pointer > other.m_pointer;
	}

	bool operator>=(CMyIterator const &other) const noexcept
	{
		return m_pointer >= other.m_pointer;
	}

	bool operator<=(CMyIterator const &other) const noexcept
	{
		return m_pointer <= other.m_pointer;
	}

	bool operator==(CMyIterator const &other) const noexcept
	{
		return m_pointer == other.m_pointer;
	}

	bool operator!=(CMyIterator const &other) const noexcept
	{
		return m_pointer != other.m_pointer;
	}

	T& operator*() const noexcept
	{
		return assert(*m_pointer);
	}

	T* operator->() const noexcept
	{
		return assert(&(*m_pointer));
	}

	T& operator[](int index) const noexcept
	{
		return assert(*(m_pointer + index));
	}

	CMyIterator const operator-(int number) const noexcept
	{
		return assert(static_cast<CMyIterator>(m_pointer - number));
	}

	ptrdiff_t const operator-(CMyIterator const & it) const noexcept
	{
		return assert(static_cast<ptrdiff_t>(m_pointer - it.m_pointer));
	}

	CMyIterator const operator+(int number) const noexcept
	{
		return assert(static_cast<CMyIterator>(m_pointer + number));
	}
};

template <typename T>
CMyIterator<T> const operator+(int number, CMyIterator<T> const & it) noexcept
{
	return assert(static_cast<CMyIterator<T>>(it.m_pointer + number));
}
