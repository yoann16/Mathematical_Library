#ifndef MY_ARRAY_H
#error Do not include this header directly. Please include TemplateArray.h
#endif


namespace Mathematical_library
{
    template<typename Type, std::size_t Size>
    Array<Type, Size>::Array()
    {
        std::fill(array, array + Size, Type{});
    }
    template<typename Type, std::size_t Size>
    Array<Type, Size>::Array(const std::initializer_list<Type>& list)
    {
        if (list.size() != Size)
            throw std::runtime_error("Size is different");
        std::copy(list.begin(), list.end(), array);
    }

    template<typename Type, std::size_t Size>
    Array<Type, Size>::Array(const Array& tab)
    {
        std::copy(tab.begin(), tab.end(), array);
    }
    template<typename Type, std::size_t Size>
    Array<Type, Size>::~Array() = default;

    template<typename Type, std::size_t Size>
    Array<Type, Size>& Array<Type, Size>::operator=(const Array& tab)
    {
        std::copy(tab.begin(), tab.end(), array);
        return *this;
    }

    template<typename Type, std::size_t Size>
    constexpr Type& Array<Type, Size>::operator[](const std::size_t position)
    {
        if (position >= Size)
            throw std::runtime_error("Index out of bounds");
        return array[position];
    }
    template<typename Type, std::size_t Size>
    constexpr const Type& Array<Type, Size>::operator[](std::size_t position) const
    {
        return array[position];
    }

    template<typename Type, std::size_t Size>
    constexpr std::size_t Array<Type, Size>::size() const
    {
        return Size;
    }
    template<typename Type, std::size_t Size>
    constexpr bool Array<Type, Size>::empty() const
    {
        return Size == 0;
    }
    template<typename Type, std::size_t Size>
    constexpr Type& Array<Type, Size>::at(std::size_t position)
    {
        if (position >= size())
            throw std::runtime_error("Index out of bounds");
        return array[position];
    }
    template<typename Type, std::size_t Size>
    constexpr const Type& Array<Type, Size>::at(std::size_t position) const
    {
        if (position >= size())
            throw std::runtime_error("Index out of bounds");
        return array[position];
    }
    template<typename Type, std::size_t Size>
    constexpr Type& Array<Type, Size>::front()
    {
        return array[0];
    }
    template<typename Type, std::size_t Size>
    constexpr const Type& Array<Type, Size>::front() const
    {
        return array[0];
    }
    template<typename Type, std::size_t Size>
    constexpr Type& Array<Type, Size>::back()
    {
        return array[Size - 1];
    }
    template<typename Type, std::size_t Size>
    constexpr const Type& Array<Type, Size>::back() const
    {
        return array[Size - 1];
    }
    template<typename Type, std::size_t Size>
    constexpr Type* Array<Type, Size>::data()
    {
        return array;
    }
    template<typename Type, std::size_t Size>
    constexpr const Type* Array<Type, Size>::data() const
    {
        return array;
    }


    template<typename Type, std::size_t Size>
    constexpr typename Array<Type, Size>::iterator Array<Type, Size>::begin() 
    {
        return array;
    }

    template<typename Type, std::size_t Size>
    constexpr typename Array<Type, Size>::const_iterator Array<Type, Size>::begin() const 
    {
        return array;
    }

    template<typename Type, std::size_t Size>
    constexpr typename Array<Type, Size>::iterator Array<Type, Size>::end() 
    {
        return array + Size;
    }

    template<typename Type, std::size_t Size>
    constexpr typename Array<Type, Size>::const_iterator Array<Type, Size>::end() const 
    {
        return array + Size;
    }


    template<typename Type, std::size_t Size>
    constexpr std::reverse_iterator<typename Array<Type, Size>::iterator> Array<Type, Size>::rbegin() 
    {
        return std::reverse_iterator<iterator>(end());
    }

    template<typename Type, std::size_t Size>
    constexpr std::reverse_iterator<typename Array<Type, Size>::const_iterator> Array<Type, Size>::rbegin() const 
    {
        return std::reverse_iterator<const_iterator>(end());
    }

    template<typename Type, std::size_t Size>
    constexpr std::reverse_iterator<typename Array<Type, Size>::iterator> Array<Type, Size>::rend() 
    {
        return std::reverse_iterator<iterator>(begin());
    }

    template<typename Type, std::size_t Size>
    constexpr std::reverse_iterator<typename Array<Type, Size>::const_iterator> Array<Type, Size>::rend() const 
    {
        return std::reverse_iterator<const_iterator>(begin());
    }

    template<typename Type, std::size_t Size>
    constexpr typename Array<Type, Size>::const_iterator Array<Type, Size>::cbegin() const
    {
        return array;
    }

    template<typename Type, std::size_t Size>
    constexpr typename Array<Type, Size>::const_iterator Array<Type, Size>::cend() const 
    {
        return array + Size;
    }

    template<typename Type, std::size_t Size>
    constexpr std::reverse_iterator<typename Array<Type, Size>::const_iterator> Array<Type, Size>::crbegin() const 
    {
        return std::reverse_iterator<const_iterator>(end());
    }

    template<typename Type, std::size_t Size>
    constexpr std::reverse_iterator<typename Array<Type, Size>::const_iterator> Array<Type, Size>::crend() const 
    {
        return std::reverse_iterator<const_iterator>(begin());
    }


    template<typename Type, std::size_t Size>
    constexpr void Array<Type, Size>::assign(const typename Array<Type, Size>::inner_type& value)
    {
        for (std::size_t i = 0; i < Size; ++i)
        {
            array[i] = value;
        }
    }
    template<typename Type, std::size_t Size>
    constexpr void Array<Type, Size>::fill(const typename Array<Type, Size>::inner_type& value)
    {
        assign(value);
    }
    template<typename Type, std::size_t Size>
    constexpr std::size_t Array<Type, Size>::max_size() const
    {
        return Size;
    }
    template<typename Type, std::size_t Size>
    constexpr void Array<Type, Size>::swap(Array& other)
    {
        for (std::size_t i = 0; i < Size; ++i)
        {
            std::swap(array[i], other.array[i]);
        }
    }

    template<typename Type, std::size_t Size>
    std::ostream& operator<<(std::ostream& os, const Array<Type, Size>& tab)
    {
        os << "(";
        for (auto i = 0;i < tab.size() - 1;++i)
            os << tab[i] << ",";

        os << tab[tab.size() - 1] << ")";
        return os;
    }
}