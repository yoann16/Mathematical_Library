// Template_Vector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <memory>
#include <cstddef>
#include <iterator>
#include <stdexcept>    // pour std::runtime_error
#include <initializer_list>
#include <cassert>
/*
* Pareil que  Array:
* at
* begin
* size
* back
*/
template<typename Type>
class Vector
{
    using iterator = Type*;
    using inner_type = Type;
    using const_iterator = const Type*;
private:
    iterator m_data;
    size_t m_size;
    size_t m_capacity;
    
public:
    Vector()
        : m_data(nullptr)
        , m_size(0)
        ,m_capacity(0)
    { }
    Vector(size_t size_init)
        : m_data(new inner_type[size_init])
        , m_size(size_init)
        , m_capacity(size_init)
    {}
    Vector(size_t size_init, const inner_type& val)
        : m_data(new inner_type[size_init])
        , m_size(size_init)
        , m_capacity(size_init)
    {
        for (size_t i = 0;i < m_size;++i)
            m_data[i] =val;
    }
    Vector(const std::initializer_list<inner_type>& list)
        : m_data(new inner_type[list.size()])
        , m_size(list.size())
        , m_capacity(list.size())
    {
        size_t i = 0;
        for (const auto& val : list)
            m_data[i++] = val;
    }
    ~Vector()
    {
        delete[] m_data;
        m_data = nullptr;
    }

    size_t size() const { return m_size;}

    size_t Capacity() const { return m_capacity; }

    inner_type& operator[](size_t index) { return m_data[index]; }

    const inner_type& operator[](size_t index) const { return m_data[index]; }

    inner_type& operator=(const Vector& other_Vector)
    { 
        if (this != &other_Vector)
            
        else
            return *this;

    }

    iterator push_back(const inner_type& value)//changer se code pour pas avoir de double if
    {
        if (m_size >= m_capacity)
        {
            if (m_capacity != 0)
                m_capacity = m_capacity * 2;
            else
                m_capacity = 1;

            iterator save = m_data;
            m_data = new inner_type[m_capacity];

            if (save!=nullptr)
                for (size_t i = 0;i < m_size;++i)
                    m_data[i] = save[i];
            delete[] save;
            save = nullptr;
        }
        m_data[m_size] = value;
        m_size++;
        return &m_data[m_size-1];
    }
};


void testVectors() 
{
    // 1. Test des constructeurs
    std::vector<int> stdVec1;                  // Constructeur par défaut
    Vector<int> myVec1;

    std::vector<int> stdVec2(5);              // Constructeur avec taille
    Vector<int> myVec2(5);

    std::vector<int> stdVec3(3, 42);          // Constructeur avec taille et valeur
    Vector<int> myVec3(3, 42);

    std::vector<int> stdVec4 = { 1,2,3,4 };     // Constructeur initializer_list
    Vector<int> myVec4 = { 1,2,3,4 };

    // 2. Test des tailles
    assert(stdVec1.size() == myVec1.size());
    assert(stdVec2.size() == myVec2.size());
    assert(stdVec3.size() == myVec3.size());
    assert(stdVec4.size() == myVec4.size());

    // 3. Test push_back et croissance
    stdVec1.push_back(1);
    myVec1.push_back(1);
    assert(stdVec1[0] == myVec1[0]);

    stdVec1.push_back(2);
    myVec1.push_back(2);
    stdVec1.push_back(3);
    myVec1.push_back(3);
    assert(stdVec1.size() == myVec1.size());

    // 4. Test d'accès aux éléments
    assert(stdVec3[0] == myVec3[0]);
    assert(stdVec3[1] == myVec3[1]);
    assert(stdVec3[2] == myVec3[2]);

    // 5. Test de modification
    stdVec2[0] = 10;
    myVec2[0] = 10;
    assert(stdVec2[0] == myVec2[0]);

    // 6. Test des cas limites
    try {
        int val = myVec1[100];  // Devrait throw une exception comme std::vector
        std::cout << "Test d'acces hors limites echoue" << std::endl;
    }
    catch (const std::out_of_range&) {
        std::cout << "Test d'acces hors limites reussi" << std::endl;
    }

    std::cout << "Tous les tests basiques ont reussi !" << std::endl;

    // Tests additionnels qu'il faudrait implémenter :
    std::cout << "\nFonctionnalités à ajouter :" << std::endl;
    std::cout << "1. operator= (affectation)" << std::endl;
    std::cout << "2. Constructeur de copie" << std::endl;
    std::cout << "3. Constructeur de déplacement" << std::endl;
    std::cout << "4. operator[] avec vérification des bornes" << std::endl;
    std::cout << "5. clear()" << std::endl;
    std::cout << "6. reserve()" << std::endl;
    std::cout << "7. resize()" << std::endl;
    std::cout << "8. empty()" << std::endl;
    std::cout << "9. at()" << std::endl;
    std::cout << "10. begin() et end()" << std::endl;
}
int main()
{
    testVectors();
    
        
}

