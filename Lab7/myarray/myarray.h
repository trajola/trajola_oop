#pragma once

template <typename T>
class CMyArray
{
public:
	CMyArray() = default;
	
	//copy constructor
	CMyArray(const CMyArray &arr)
	{
		const auto size = arr.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			try
			{
				CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
				m_endOfCapacity = m_end;
			}
			catch (...)
			{
				DeleteItems(m_begin, m_end);
				throw;
			}
		}
	}

	//move construstor
	CMyArray(CMyArray &&arr)
		:m_begin(arr.m_begin)
		, m_end(arr.m_end)
		, m_endOfCapacity(arr.m_endOfCapacity)
	{
		arr.m_begin = nullptr;
		arr.m_end = nullptr;
		arr.m_endOfCapacity = nullptr;
	}

	~CMyArray()
	{
		DeleteItems(m_begin, m_end);
	}

	size_t GetCapacity() const noexcept
	{
		return m_endOfCapacity - m_begin;
	}

	size_t GetSize() const noexcept
	{
		return m_end - m_begin;
	}

	void Append(const T & value)
	{
		if (m_end == m_endOfCapacity) // no free space
		{
			size_t newCapacity = std::max(size_t(1), GetCapacity() * 2);

			auto newBegin = RawAlloc(newCapacity);
			T *newEnd = newBegin;
			try
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);
				new (newEnd)T(value);
				++newEnd;
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}
			DeleteItems(m_begin, m_end);

			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + newCapacity;
		}
		else // has free space
		{
			new (m_end) T(value);
			++m_end;
		}
	}

	void Resize(size_t newSize)
	{
		size_t currentSize = GetSize();
		if (currentSize <= newSize)
		{
			for (size_t i = 0; i < newSize - currentSize; ++i)
				Append(T());
		}
		else
		{
			DestroyItems(m_begin + newSize, m_end);
			m_end = m_begin + newSize;
		}
	}

	void Clear() noexcept
	{
		DestroyItems(m_begin, m_end);
		m_end = m_begin;
	}

	CMyArray &operator = (CMyArray && rhs) noexcept //move=
	{
		if (&rhs != this)
		{
			Clear();
			m_begin = rhs.m_begin;
			m_end = rhs.m_end;
			m_endOfCapacity = rhs.m_endOfCapacity;

			rhs.m_begin = nullptr;
			rhs.m_end = nullptr;
			rhs.m_endOfCapacity = nullptr;
		}
		return *this;
	}

	CMyArray &operator = (CMyArray const &rhs) noexcept //copy=
	{
		if (this != std::addressof(rhs))
		{
			CMyArray newArray(rhs);
			std::swap(m_begin, newArray.m_begin);
			std::swap(m_end, newArray.m_end);
			std::swap(m_endOfCapacity, newArray.m_endOfCapacity);
		}
		return *this;
	}

	T &operator[](size_t position)
	{
		if (position >= GetSize())
			throw std::out_of_range("Out of range");
		return m_begin[position];
	}

	const T &operator[](size_t position) const
	{
		if (position >= GetSize())
			throw std::out_of_range("Out of range");
		return m_begin[position];
	}
private:
	template <typename T>
	class CMyIterator
	{
	public:
		CMyIterator(T* p = nullptr) noexcept
			: m_pointer(p)
		{
		};

		CMyIterator& operator--() noexcept
		{
			--m_pointer;
			return *this;
		};

		CMyIterator& operator++() noexcept
		{
			++m_pointer;
			return *this;
		};

		bool operator<(CMyIterator const &other) const noexcept
		{
			return m_pointer < other.m_pointer;
		};

		bool operator>(CMyIterator const &other) const noexcept
		{
			return m_pointer > other.m_pointer;
		};

		bool operator>=(CMyIterator const &other) const noexcept
		{
			return m_pointer >= other.m_pointer;
		};

		bool operator<=(CMyIterator const &other) const noexcept
		{
			return m_pointer <= other.m_pointer;
		};

		bool operator==(CMyIterator const &other) const noexcept
		{
			return m_pointer == other.m_pointer;
		};

		bool operator!=(CMyIterator const &other) const noexcept
		{
			return m_pointer != other.m_pointer;
		};

		size_t operator-(CMyIterator const &other) const noexcept
		{
			return m_pointer - other.m_pointer;
		};

		CMyIterator operator+(size_t number) const noexcept
		{
			return static_cast<CMyIterator>(m_pointer + number);
		};

		CMyIterator operator-(size_t number) const noexcept
		{
			return static_cast<CMyIterator>(m_pointer - number);
		};

		T& operator*() const noexcept
		{
			return *m_pointer;
		};

		T* operator->() const noexcept
		{
			return &(*m_pointer);
		};

		T& operator[](size_t index) const noexcept
		{
			return *(m_pointer + index);
		};

	private:
		CMyIterator() noexcept;
		T * m_pointer = nullptr;
	};

public:	
	CMyIterator<T> begin() const noexcept
	{
		return CMyIterator<T>(m_begin);
	};

	CMyIterator<T> end() const noexcept
	{
		return CMyIterator<T>(m_end);
	};
	
private:
	static T *RawAlloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T *p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void RawDealloc(T *p)
	{
		free(p);
	}

	static void CopyItems(const T *srcBegin, T *srcEnd, T * const dstBegin, T * & dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			new (dstEnd)T(*srcBegin);
		}
	}

	static void DeleteItems(T *begin, T *end)
	{
		DestroyItems(begin, end);
		RawDealloc(begin);
	}

	static void DestroyItems(T *from, T *to) noexcept
	{
		while (to != from)
		{
			--to;
			to->~T();
		}
	}	

	T * m_begin = nullptr;
	T *m_end = nullptr;
	T *m_endOfCapacity = nullptr;
};