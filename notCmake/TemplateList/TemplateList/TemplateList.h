#ifndef MY_TEMPLATE_LIST_H
#define MY_TEMPLATE_LIST_H

#include <initializer_list>
#include <iterator>

template<typename T>
class List {
private:
    struct Node;

public:
    // Iterateurs
    class iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(Node* ptr = nullptr) : m_ptr(ptr) {}

        iterator& operator++() { m_ptr = m_ptr->next; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
        iterator& operator--() { m_ptr = m_ptr->previous; return *this; }
        iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }

        bool operator==(const iterator& other) const { return m_ptr == other.m_ptr; }
        bool operator!=(const iterator& other) const { return !(*this == other); }

        T& operator*() { return m_ptr->value; }
        T* operator->() { return &m_ptr->value; }

    private:
        Node* m_ptr;
        friend class List;
    };

    class const_iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator(Node* ptr = nullptr) : m_ptr(ptr) {}

        const_iterator& operator++() { m_ptr = m_ptr->next; return *this; }
        const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }
        const_iterator& operator--() { m_ptr = m_ptr->previous; return *this; }
        const_iterator operator--(int) { const_iterator tmp = *this; --(*this); return tmp; }

        bool operator==(const const_iterator& other) const { return m_ptr == other.m_ptr; }
        bool operator!=(const const_iterator& other) const { return !(*this == other); }

        const T& operator*() const { return m_ptr->value; }
        const T* operator->() const { return &m_ptr->value; }

    private:
        Node* m_ptr;
        friend class List;
    };

    // Constructeurs et destructeur
    List();
    List(const List& other);  // Constructeur de copie
    List(List&& other) noexcept;  // Constructeur de déplacement
    List(std::initializer_list<T> init);  // Constructeur avec initializer_list
    List(size_t count, const T& value);  // Constructeur avec n copies
    template<typename InputIt>
    List(InputIt first, InputIt last);  // Constructeur avec itérateurs
    ~List();

    // Opérateurs d'affectation
    List& operator=(const List& other);
    List& operator=(List&& other) noexcept;
    List& operator=(std::initializer_list<T> ilist);

    // Itérateurs
    iterator begin() { return iterator(m_first); }
    iterator end() { return iterator(nullptr); }
    const_iterator begin() const { return const_iterator(m_first); }
    const_iterator end() const { return const_iterator(nullptr); }
    const_iterator cbegin() const { return const_iterator(m_first); }
    const_iterator cend() const { return const_iterator(nullptr); }

    // Capacité
    bool empty() const;
    size_t size() const;
    void clear();

    // Accès aux éléments
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    // Modificateurs
    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();

    iterator insert(const_iterator pos, const T& value);
    iterator insert(const_iterator pos, size_t count, const T& value);
    template<typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last);
    iterator insert(const_iterator pos, std::initializer_list<T> ilist);

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);

    void swap(List& other) noexcept;
    void resize(size_t count);
    void resize(size_t count, const T& value);

    // Opérateurs de comparaison
    bool operator==(const List& other) const;
    bool operator!=(const List& other) const;
    bool operator<(const List& other) const;
    bool operator<=(const List& other) const;
    bool operator>(const List& other) const;
    bool operator>=(const List& other) const;

private:
    struct Node {
        Node(const T& value_) : value(value_), previous(nullptr), next(nullptr) {}
        T value;
        Node* previous;
        Node* next;
    };

    Node* m_first;
    Node* m_last;

   
};

#endif

#include "TemplateListImpl.h"