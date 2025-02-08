#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <initializer_list>
#include <iterator>

namespace Mathematical_library
{
	template<typename Type>
	class Vector
	{
		using iterator = Type*;
		using inner_type = Type;
		using const_iterator = const Type*;
		using size_type = std::size_t;
	private:
		iterator m_data;
		size_t m_size;
		size_t m_capacity;

	public:
		Vector()
			: m_data(nullptr)
			, m_size(0)
			, m_capacity(0)
		{
		}
		Vector(size_t size_init)
			: m_data(new inner_type[size_init])
			, m_size(size_init)
			, m_capacity(size_init)
		{
		}
		Vector(size_t size_init, const inner_type& val)
			: m_data(new inner_type[size_init])
			, m_size(size_init)
			, m_capacity(size_init)
		{
			for (auto it = begin();it != end();++it)
				*it = val;
		}
		Vector(const std::initializer_list<inner_type>& list)
			: m_data(new inner_type[list.size()])
			, m_size(list.size())
			, m_capacity(list.size())
		{
			size_t index = 0;
			for (const auto& val : list)
				m_data[index++] = val;
		}
		Vector(const Vector& other_Vector)
			: m_data(new inner_type[other_Vector.size()])
			, m_size(other_Vector.size())
			, m_capacity(other_Vector.size())
		{
			for (size_t index = 0; index < m_size; ++index)
				m_data[index] = other_Vector[index];
		}
		Vector(Vector&& other_Vector)noexcept

		{
			m_data = other_Vector.m_data;
			m_size = other_Vector.m_size;
			m_capacity = other_Vector.m_capacity;

			other_Vector.m_data = nullptr;
			other_Vector.m_size = 0;
			other_Vector.m_capacity = 0;
		}
		~Vector()
		{
			delete[] m_data;
			m_data = nullptr;
		}

		constexpr size_t size() const { return m_size; }

		constexpr bool empty() const { return m_size == 0; }

		constexpr size_t capacity() const { return m_capacity; }

		inner_type& operator[](size_t index)
		{
			if (index >= m_size)
				throw std::out_of_range("Out of Range");
			return m_data[index];
		}

		const inner_type& operator[](size_t index) const
		{
			if (index >= m_size)
				throw std::out_of_range("Out of Range");
			return m_data[index];
		}

		Vector& operator=(const Vector& other_Vector)
		{
			if (this != &other_Vector)
			{
				delete[] m_data;
				m_data = nullptr;
				m_capacity = other_Vector.capacity();
				m_size = other_Vector.size();
				m_data = new inner_type[m_capacity];
				for (size_t index = 0;index < m_size;++index)
					m_data[index] = other_Vector[index];

			}
			return *this;

		}
		Vector& operator=(Vector&& other_Vector) noexcept
		{
			if (this != &other_Vector)
			{
				delete[] m_data;
				m_data = other_Vector.m_data;
				m_capacity = other_Vector.capacity();
				m_size = other_Vector.size();


				other_Vector.m_data = nullptr;
				other_Vector.m_capacity = 0;
				other_Vector.m_size = 0;
			}
			return *this;
		}


		bool operator==(const Vector& other) const
		{
			if (size() != other.size())
				return false;

			for (std::size_t i = 0; i < size(); ++i)
			{
				if (m_data[i] != other.m_data[i])
					return false;
			}
			return true;
		}

		bool operator<(const Vector& other) const
		{
			const size_t min_size = std::min(size(), other.size());

			for (std::size_t i = 0; i < min_size; ++i)
			{
				if (m_data[i] < other.m_data[i])
					return true;
				if (m_data[i] > other.m_data[i])
					return false;
			}

			return size() < other.size();
		}
		bool operator!=(const Vector& other) const { return !(*this == other); }
		bool operator>(const Vector& other) const { return other < *this; }
		bool operator<=(const Vector& other) const { return !(other < *this); }
		bool operator>=(const Vector& other) const { return !(*this < other); }

		iterator push_back(const inner_type& value)
		{
			if (m_size >= m_capacity)
			{
				size_t new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
				reserve(new_capacity);
			}
			m_data[m_size] = value;
			m_size++;
			return &m_data[m_size - 1];
		}
		void pop_back()
		{
			if (empty() == true)
				throw std::runtime_error("The Vector is empty");
			m_data[m_size - 1].~Type();
			--m_size;
		}
		iterator insert(const_iterator pos, const inner_type& value)
		{
			if (pos < begin() || pos > end())
			{
				throw std::out_of_range("Invalid insert position");
			}

			size_t index = pos - begin();

			if (m_size >= m_capacity)
			{
				reserve(m_capacity == 0 ? 1 : m_capacity * 2);
			}

			for (size_t i = m_size; i > index; --i)
			{
				m_data[i] = std::move(m_data[i - 1]);
			}

			m_data[index] = value;
			++m_size;

			return begin() + index;
		}
		iterator insert(const_iterator pos, size_type count, const Type& value)
		{
			if (pos < begin() || pos > end())
			{
				throw std::out_of_range("Invalid insert position");
			}

			size_type index = pos - begin();

			if (m_size + count > m_capacity)
			{
				size_type new_capacity = std::max(m_capacity * 2, m_size + count);
				reserve(new_capacity);
			}

			for (size_type i = m_size + count - 1; i > index + count - 1; --i)
			{
				m_data[i] = std::move(m_data[i - count]);
			}

			for (size_type i = 0; i < count; ++i)
			{
				m_data[index + i] = value;
			}

			m_size += count;

			return begin() + index;
		}
		iterator erase(const_iterator pos)
		{
			if (pos < begin() || pos >= end())
			{
				throw std::out_of_range("Invalid erase position");
			}
			size_t index = pos - begin();
			for (size_t i = index; i < m_size - 1; ++i)
			{
				m_data[i] = std::move(m_data[i + 1]);
			}
			--m_size;
			return begin() + index;
		}
		iterator erase(const_iterator first, const_iterator last)
		{
			if (first < begin() || last > end() || first > last)
			{
				throw std::out_of_range("Invalid erase range");
			}


			size_t start_index = first - begin();
			size_t end_index = last - begin();
			size_t count = end_index - start_index;


			for (size_t i = end_index; i < m_size; ++i)
			{
				m_data[i - count] = std::move(m_data[i]);
			}


			m_size -= count;


			return begin() + start_index;
		}

		inner_type& at(size_t index)
		{
			if (index >= m_size)
				throw std::out_of_range("Out of Range");
			return m_data[index];
		}
		const inner_type& at(size_t index) const
		{
			if (index >= m_size)
				throw std::out_of_range("Out of Range");
			return m_data[index];
		}
		void clear()
		{
			for (auto it = begin(); it != end(); ++it)
				it->~Type();
			m_size = 0;
		}
		void reserve(size_t new_capacity)
		{
			if (new_capacity > m_capacity)
			{
				inner_type* new_data = new inner_type[new_capacity];

				for (size_t index = 0; index < m_size; ++index)
					new_data[index] = m_data[index];

				delete[] m_data;
				m_data = new_data;
				m_capacity = new_capacity;
			}
		}
		void resize(size_t new_size, const inner_type& val = inner_type())
		{
			if (new_size > m_size)
			{
				if (new_size > m_capacity)
					reserve(new_size);
				for (size_t index = m_size; index < new_size;++index)
					m_data[index] = val;
			}
			m_size = new_size;
		}

		constexpr inner_type& front()
		{
			if (empty())
				throw std::out_of_range("Vector is empty");
			return m_data[0];
		}
		constexpr const inner_type& front() const
		{
			if (empty())
				throw std::out_of_range("Vector is empty");
			return m_data[0];
		}
		constexpr inner_type& back()
		{
			if (empty())
				throw std::out_of_range("Vector is empty");
			return m_data[m_size - 1];
		}
		constexpr const inner_type& back() const
		{
			if (empty())
				throw std::out_of_range("Vector is empty");
			return m_data[m_size - 1];
		}
		constexpr iterator data() { return m_data; }
		constexpr const_iterator data() const { return m_data; }

		void swap(Vector& other_Vector) noexcept
		{
			std::swap(m_data, other_Vector.m_data);
			std::swap(m_size, other_Vector.m_size);
			std::swap(m_capacity, other_Vector.m_capacity);
		}


		constexpr iterator begin() noexcept { return m_data; }
		constexpr const_iterator begin() const noexcept { return m_data; }
		constexpr const_iterator cbegin() const noexcept { return m_data; }
		constexpr std::reverse_iterator<iterator> rbegin() noexcept { return std::reverse_iterator<iterator>(end()); }
		constexpr std::reverse_iterator<const_iterator> rbegin() const noexcept { return std::reverse_iterator<const_iterator>(end()); }
		constexpr std::reverse_iterator<const_iterator> crbegin() const noexcept { return std::reverse_iterator<const_iterator>(cend()); }

		constexpr iterator end() noexcept { return m_data + m_size; }
		constexpr const_iterator end() const noexcept { return m_data + m_size; }
		constexpr const_iterator cend() const noexcept { return m_data + m_size; }
		constexpr std::reverse_iterator<iterator> rend() noexcept { return std::reverse_iterator<iterator>(begin()); }
		constexpr std::reverse_iterator<const_iterator> rend() const noexcept { return std::reverse_iterator<const_iterator>(begin()); }
		constexpr std::reverse_iterator<const_iterator> crend() const noexcept { return std::reverse_iterator<const_iterator>(cbegin()); }


	};
}
#endif

