// Template_Vector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <memory>
#include <cstddef>
#include <iterator>
#include <stdexcept>    // pour std::runtime_error
#include <initializer_list>
/*
* Pareil que  Array:
* at
* begin
* size
* back
*/
template<typename Type, typename Allocator = std::allocator<Type>>
class Vector
{
    using iterator = Type*;
    using inner_type = Type;
    using const_iterator = const Type*;
private:
    iterator data_;
    size_t size_;
    size_t capacity_;
    Allocator alloc_;
public:
    Vector()
        :data_(nullptr)
        ,size_(0)
        ,capacity_(0)
    { }
    Vector(const std::initializer_list<inner_type>& list)
        :data_(nullptr)
        , size_(0)
        , capacity_(0)
    {
        for (const auto& item : list) 
        {
            push_back(item);
        }
    }
    Vector(const Vector& tab)
        :data_(nullptr)
        , size_(0)
        , capacity_(0)
    {
        if (tab.size_ > 0) {
            data_ = std::allocator_traits<Allocator>::allocate(alloc_, tab.size_);
            capacity_ = tab.size_;
            size_ = tab.size_;

            for (size_t i = 0; i < size_; ++i) {
                std::allocator_traits<Allocator>::construct(alloc_, data_ + i, tab.data_[i]);
            }
        }
    }
    ~Vector()
    {
        for (size_t i=0;i< size_;++i)
            std::allocator_traits<Allocator>::destroy(alloc_, data_ + i);
        if(data_)
            std::allocator_traits<Allocator>::deallocate(alloc_, data_, capacity_);

    }
    size_t size() const { return size_; }
    constexpr std::size_t max_size() const { return std::allocator_traits<Allocator>::max_size(alloc_); }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    iterator begin() { return data_; }
    iterator end() { return data_ + size_; }
    const_iterator begin() const { return data_; }
    const_iterator end() const { return data_ + size_; }

    Type& operator[](size_t index) { return data_[index]; }
    const Type& operator[](size_t index) const { return data_[index]; }
    Vector& operator=(const Vector& tab) 
    {
        if (this != &tab) 
        {
            // Nettoyage de l'ancien contenu
            for (size_t i = 0; i < size_; ++i) 
                std::allocator_traits<Allocator>::destroy(alloc_, data_ + i);
            if (data_) 
                std::allocator_traits<Allocator>::deallocate(alloc_, data_, capacity_);

            // Copie du nouveau contenu
            if (tab.size_ > 0) 
            {
                data_ = std::allocator_traits<Allocator>::allocate(alloc_, tab.size_);
                capacity_ = tab.size_;
                size_ = tab.size_;

                for (size_t i = 0; i < size_; ++i) 
                    std::allocator_traits<Allocator>::construct(alloc_, data_ + i, tab.data_[i]);
            }
            else 
            {
                data_ = nullptr;
                size_ = capacity_ = 0;
            }
        }
        return *this;
    }

    constexpr inner_type& at(std::size_t index)
    {
        if (index >= size())
            throw std::runtime_error("Index out of bounds");
        return data_[index];
    }
    constexpr const inner_type& at(std::size_t index) const
    {
        if (index >= size())
            throw std::runtime_error("Index out of bounds");
        return data_[index];
    }

    constexpr inner_type& front() { return data_[0]; }
    constexpr const inner_type& front() const { return data_[0]; }

    constexpr inner_type& back() { return data_[size_ - 1 ]; }
    constexpr const inner_type& back() const { return data_[size_ - 1]; }

    constexpr inner_type* data() { return data_; }
    constexpr const inner_type* data() const { return data_; }

    constexpr std::reverse_iterator<iterator> rbegin() { return std::reverse_iterator<iterator>(end()); }
    constexpr std::reverse_iterator<const_iterator> rbegin() const { return std::reverse_iterator<iterator>(end()); }

    constexpr std::reverse_iterator<iterator> rend() { return std::reverse_iterator<iterator>(begin()); }
    constexpr std::reverse_iterator<const_iterator> rend() const { return std::reverse_iterator<iterator>(begin()); }


    constexpr const_iterator cbegin() const { return data_; }

    constexpr const_iterator cend() const { return data_ + size_; }


    constexpr std::reverse_iterator<const_iterator> crbegin() const { return std::reverse_iterator<iterator>(end()); }

    constexpr std::reverse_iterator<const_iterator> crend() const { return std::reverse_iterator<iterator>(begin()); }

    constexpr void assign(const inner_type& value)
    {
        for (std::size_t i = 0; i < size_; ++i)
        {
            data_[i] = value;
        }
    }
    constexpr void swap(Vector& other)
    {
        for (std::size_t i = 0; i < size_; ++i)
        {
            std::swap(data_[i], other.data_[i]);
        }
    }
    void push_back(const Type& value) {
        if (size_ == capacity_) {
            // Réallocation nécessaire
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;

            // Allouer un nouveau tableau plus grand
            Type* new_data = std::allocator_traits<Allocator>::allocate(alloc_, new_capacity);

            // Copier les anciens éléments
            for (size_t i = 0; i < size_; ++i) {
                std::allocator_traits<Allocator>::construct(alloc_, new_data + i, data_[i]);
                std::allocator_traits<Allocator>::destroy(alloc_, data_ + i);
            }

            // Libérer l'ancien tableau
            if (data_) {
                std::allocator_traits<Allocator>::deallocate(alloc_, data_, capacity_);
            }

            data_ = new_data;
            capacity_ = new_capacity;
        }

        // Ajouter le nouvel élément
        std::allocator_traits<Allocator>::construct(alloc_, data_ + size_, value);
        ++size_;
    }
    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("Vector is empty");
        }
        std::allocator_traits<Allocator>::destroy(alloc_, data_ + size_ - 1);
        --size_;
    }
    void resize(size_t new_size) {
        if (new_size > capacity_) {
            // Besoin de réallouer
            reserve(new_size);
        }
        // Si on agrandit, construire les nouveaux éléments
        for (size_t i = size_; i < new_size; ++i) {
            std::allocator_traits<Allocator>::construct(alloc_, data_ + i);
        }
        // Si on réduit, détruire les éléments en trop
        for (size_t i = new_size; i < size_; ++i) {
            std::allocator_traits<Allocator>::destroy(alloc_, data_ + i);
        }
        size_ = new_size;
    }
    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            Type* new_data = std::allocator_traits<Allocator>::allocate(alloc_, new_capacity);

            for (size_t i = 0; i < size_; ++i) {
                std::allocator_traits<Allocator>::construct(alloc_, new_data + i, data_[i]);
                std::allocator_traits<Allocator>::destroy(alloc_, data_ + i);
            }

            if (data_) {
                std::allocator_traits<Allocator>::deallocate(alloc_, data_, capacity_);
            }

            data_ = new_data;
            capacity_ = new_capacity;
        }
    }
    void clear() {
        for (size_t i = 0; i < size_; ++i) {
            std::allocator_traits<Allocator>::destroy(alloc_, data_ + i);
        }
        size_ = 0;
    }
    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (size_ == capacity_) {
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reserve(new_capacity);
        }
        std::allocator_traits<Allocator>::construct(alloc_, data_ + size_, std::forward<Args>(args)...);
        ++size_;
    }
    void shrink_to_fit() {
        if (size_ < capacity_) {
            Type* new_data = nullptr;
            if (size_ > 0) {
                new_data = std::allocator_traits<Allocator>::allocate(alloc_, size_);
                for (size_t i = 0; i < size_; ++i) {
                    std::allocator_traits<Allocator>::construct(alloc_, new_data + i, data_[i]);
                    std::allocator_traits<Allocator>::destroy(alloc_, data_ + i);
                }
            }

            if (data_) {
                std::allocator_traits<Allocator>::deallocate(alloc_, data_, capacity_);
            }

            data_ = new_data;
            capacity_ = size_;
        }
    }

    iterator insert(const_iterator pos, const Type& value) {
        size_t index = pos - begin();
        if (size_ == capacity_) {
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reserve(new_capacity);
        }

        for (size_t i = size_; i > index; --i) {
            std::allocator_traits<Allocator>::construct(alloc_, data_ + i, data_[i - 1]);
            std::allocator_traits<Allocator>::destroy(alloc_, data_ + i - 1);
        }

        std::allocator_traits<Allocator>::construct(alloc_, data_ + index, value);
        ++size_;

        return begin() + index;
    }

    iterator erase(const_iterator pos) {
        size_t index = pos - begin();
        std::allocator_traits<Allocator>::destroy(alloc_, data_ + index);

        for (size_t i = index; i < size_ - 1; ++i) {
            std::allocator_traits<Allocator>::construct(alloc_, data_ + i, data_[i + 1]);
            std::allocator_traits<Allocator>::destroy(alloc_, data_ + i + 1);
        }

        --size_;
        return begin() + index;
    }

    template<typename... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        size_t index = pos - begin();
        if (size_ == capacity_) {
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reserve(new_capacity);
        }

        for (size_t i = size_; i > index; --i) {
            std::allocator_traits<Allocator>::construct(alloc_, data_ + i, data_[i - 1]);
            std::allocator_traits<Allocator>::destroy(alloc_, data_ + i - 1);
        }

        std::allocator_traits<Allocator>::construct(alloc_, data_ + index, std::forward<Args>(args)...);
        ++size_;

        return begin() + index;
    }

    Allocator get_allocator() const noexcept {
        return alloc_;
    }
};
int main()
{
    std::cout << "Hello World!\n";
    std::vector<int> vect;
    //vect
        
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
