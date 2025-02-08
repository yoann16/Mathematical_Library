#ifndef MY_ARRAY_H
#define MY_ARRAY_H

#include <iostream>
#include <stdexcept>
#include <iterator>
#include <initializer_list>



namespace Mathematical_library
{
    template<typename Type, std::size_t Size>
    class Array
    {
        using iterator = Type*;
        using inner_type = Type;
        using const_iterator = const Type*;

        template<typename Type, std::size_t Size>
        friend std::ostream& operator<<(std::ostream& os, const Array& tab);

    private:
        Type array[Size];
    public:
        Array();
        Array(const std::initializer_list<inner_type>& list);
        Array(const Array& tab);
        ~Array();

        Array& operator=(const Array& tab);
        constexpr inner_type& operator[](const std::size_t position);
        constexpr const inner_type& operator[](std::size_t position) const;

        
        bool operator==(const Array& other) const;

        
        bool operator!=(const Array& other) const;

        
        bool operator<(const Array& other) const;

        
        bool operator>(const Array& other) const;

        
        bool operator<=(const Array& other) const;

        
        bool operator>=(const Array& other) const;

        constexpr std::size_t size() const;
        constexpr std::size_t max_size() const;
        constexpr bool empty() const;

        constexpr inner_type& at(std::size_t position);
        constexpr const inner_type& at(std::size_t position) const;

        constexpr inner_type& front();
        constexpr const inner_type& front() const;

        constexpr inner_type& back();
        constexpr const inner_type& back() const;

        constexpr inner_type* data();
        constexpr const inner_type* data() const;


        constexpr iterator begin();
        constexpr  const_iterator begin() const;

        constexpr iterator end();
        constexpr const_iterator end() const;


        constexpr std::reverse_iterator<iterator> rbegin();
        constexpr std::reverse_iterator<const_iterator> rbegin() const;

        constexpr std::reverse_iterator<iterator> rend();
        constexpr std::reverse_iterator<const_iterator> rend() const;


        constexpr const_iterator cbegin() const;

        constexpr const_iterator cend() const;


        constexpr std::reverse_iterator<const_iterator> crbegin() const;

        constexpr std::reverse_iterator<const_iterator> crend() const;

        constexpr void assign(const inner_type& value);
        constexpr void fill(const inner_type& value);
        constexpr void swap(Array& other);
    };

    
}
#endif

#include "TemplateArrayImpl.h"
