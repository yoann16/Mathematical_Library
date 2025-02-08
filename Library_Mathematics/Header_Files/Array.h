#ifndef MY_ARRAY_H
#define MY_ARRAY_H

#include <iostream>
#include <stdexcept>
#include <iterator>
#include <initializer_list>

namespace Mathematical_library
{
    /**
     * \brief Static array container with fixed size
     *
     * \tparam Type The type of elements stored in the array
     * \tparam Size The static size of the array
     */
    template<typename Type, std::size_t Size>
    class Array
    {
        using iterator = Type*;
        using inner_type = Type;
        using const_iterator = const Type*;

        template<typename Type, std::size_t Size>
        friend std::ostream& operator<<(std::ostream& os, const Array& tab);

    protected:
        Type array[Size];

    public:
        /**
         * \brief Default constructor
         *
         * \details Initializes all elements to their default value
         */
        Array();

        /**
         * \brief Constructor from initializer list
         *
         * \param list Initializer list of elements
         * \throws std::runtime_error If list size does not match array size
         */
        Array(const std::initializer_list<inner_type>& list);

        /**
         * \brief Copy constructor
         *
         * \param tab Array to copy
         */
        Array(const Array& tab);

        /**
         * \brief Destructor
         */
        ~Array();

        /**
         * \brief Assignment operator
         *
         * \param tab Array to copy
         * \return Reference to the current array
         */
        Array& operator=(const Array& tab);

        /**
         * \brief Element access operator (non-const)
         *
         * \param position Index of the element
         * \return Reference to the element
         * \throws std::runtime_error If index is out of bounds
         */
        constexpr inner_type& operator[](const std::size_t position);

        /**
         * \brief Element access operator (const)
         *
         * \param position Index of the element
         * \return Const reference to the element
         */
        constexpr const inner_type& operator[](std::size_t position) const;

        /**
         * \brief Equality comparison operator
         *
         * \param other Array to compare
         * \return \c true if arrays are equal, \c false otherwise
         */
        bool operator==(const Array& other) const;

        /**
         * \brief Inequality comparison operator
         *
         * \param other Array to compare
         * \return \c true if arrays are not equal, \c false otherwise
         */
        bool operator!=(const Array& other) const;

        /**
         * \brief Less than comparison operator
         *
         * \param other Array to compare
         * \return \c true if current array is lexicographically less, \c false otherwise
         */
        bool operator<(const Array& other) const;

        /**
         * \brief Greater than comparison operator
         *
         * \param other Array to compare
         * \return \c true if current array is lexicographically greater, \c false otherwise
         */
        bool operator>(const Array& other) const;

        /**
         * \brief Less than or equal to comparison operator
         *
         * \param other Array to compare
         * \return \c true if current array is lexicographically less or equal, \c false otherwise
         */
        bool operator<=(const Array& other) const;

        /**
         * \brief Greater than or equal to comparison operator
         *
         * \param other Array to compare
         * \return \c true if current array is lexicographically greater or equal, \c false otherwise
         */
        bool operator>=(const Array& other) const;

        /**
         * \brief Get the size of the array
         *
         * \return Size of the array
         */
        constexpr std::size_t size() const;

        /**
         * \brief Get the maximum size of the array
         *
         * \return Maximum size of the array
         */
        constexpr std::size_t max_size() const;

        /**
         * \brief Check if the array is empty
         *
         * \return \c true if size is 0, \c false otherwise
         */
        constexpr bool empty() const;

        /**
         * \brief Access element with bounds checking (non-const)
         *
         * \param position Index of the element
         * \return Reference to the element
         * \throws std::runtime_error If index is out of bounds
         */
        constexpr inner_type& at(std::size_t position);

        /**
         * \brief Access element with bounds checking (const)
         *
         * \param position Index of the element
         * \return Const reference to the element
         * \throws std::runtime_error If index is out of bounds
         */
        constexpr const inner_type& at(std::size_t position) const;

        /**
         * \brief Access the first element (non-const)
         *
         * \return Reference to the first element
         */
        constexpr inner_type& front();

        /**
         * \brief Access the first element (const)
         *
         * \return Const reference to the first element
         */
        constexpr const inner_type& front() const;

        /**
         * \brief Access the last element (non-const)
         *
         * \return Reference to the last element
         */
        constexpr inner_type& back();

        /**
         * \brief Access the last element (const)
         *
         * \return Const reference to the last element
         */
        constexpr const inner_type& back() const;

        /**
         * \brief Get pointer to array data (non-const)
         *
         * \return Pointer to the first element
         */
        constexpr inner_type* data();

        /**
         * \brief Get pointer to array data (const)
         *
         * \return Const pointer to the first element
         */
        constexpr const inner_type* data() const;

        /**
         * \brief Return iterator to beginning (non-const)
         *
         * \return Iterator to the first element
         */
        constexpr iterator begin();

        /**
         * \brief Return const iterator to beginning
         *
         * \return Const iterator to the first element
         */
        constexpr const_iterator begin() const;

        /**
         * \brief Return iterator to end (non-const)
         *
         * \return Iterator to the element after the last
         */
        constexpr iterator end();

        /**
         * \brief Return const iterator to end
         *
         * \return Const iterator to the element after the last
         */
        constexpr const_iterator end() const;

        /**
         * \brief Return reverse iterator to beginning (non-const)
         *
         * \return Reverse iterator to the last element
         */
        constexpr std::reverse_iterator<iterator> rbegin();

        /**
         * \brief Return const reverse iterator to beginning
         *
         * \return Const reverse iterator to the last element
         */
        constexpr std::reverse_iterator<const_iterator> rbegin() const;

        /**
         * \brief Return reverse iterator to end (non-const)
         *
         * \return Reverse iterator to the element before the first
         */
        constexpr std::reverse_iterator<iterator> rend();

        /**
         * \brief Return const reverse iterator to end
         *
         * \return Const reverse iterator to the element before the first
         */
        constexpr std::reverse_iterator<const_iterator> rend() const;

        /**
         * \brief Return const iterator to beginning
         *
         * \return Const iterator to the first element
         */
        constexpr const_iterator cbegin() const;

        /**
         * \brief Return const iterator to end
         *
         * \return Const iterator to the element after the last
         */
        constexpr const_iterator cend() const;

        /**
         * \brief Return const reverse iterator to beginning
         *
         * \return Const reverse iterator to the last element
         */
        constexpr std::reverse_iterator<const_iterator> crbegin() const;

        /**
         * \brief Return const reverse iterator to end
         *
         * \return Const reverse iterator to the element before the first
         */
        constexpr std::reverse_iterator<const_iterator> crend() const;

        /**
         * \brief Assign a value to all array elements
         *
         * \param value Value to assign
         */
        constexpr void assign(const inner_type& value);

        /**
         * \brief Fill the array with a given value
         *
         * \param value Fill value
         */
        constexpr void fill(const inner_type& value);

        /**
         * \brief Swap the contents of two arrays
         *
         * \param other Array to swap with the current array
         */
        constexpr void swap(Array& other);
    };
    
}
#include "ArrayImpl.h"
#endif
