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
		for ( auto it = begin();it != end();++it)
			*it =val;
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

	constexpr size_t size() const { return m_size;}

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
			m_data= new inner_type[m_capacity];
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
		for (std::size_t i = 0; i < size(); ++i)
		{
			if (m_data[i] != other.m_data[i])
				return false;
		}
		return true;
	}

	
	bool operator!=(const Vector& other) const { return !(*this == other); }

	
	bool operator<(const Vector& other) const
	{
		for (std::size_t i = 0; i < size(); ++i)
		{
			if (m_data[i] < other.m_data[i])
				return true;
			if (m_data[i] > other.m_data[i])
				return false;
		}
		return false;
	}

	
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
		return &m_data[m_size-1];
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
	
	constexpr inner_type& front() {return m_data[0];}
	constexpr const inner_type& front() const {return m_data[0];}

	constexpr inner_type& back(){return m_data[size() - 1];}
	constexpr const inner_type& back() const {return m_data[size() - 1]; }
	
	constexpr iterator data(){return m_data;}
	constexpr const_iterator data() const {return m_data;}

	void swap(Vector& other_Vector) noexcept
	{
		std::swap(m_data, other_Vector.m_data);
		std::swap(m_size, other_Vector.m_size);
		std::swap(m_capacity, other_Vector.m_capacity);
	}
	

	constexpr iterator begin() noexcept{ return m_data; }
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
void testErase()
{
	// Detailed erase testing
	{
		Vector<int> eraseVec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		// Erase single element
		auto eraseIt = eraseVec.erase(eraseVec.begin() + 2);

		// Verify the iterator points to the correct element
		assert(eraseIt - eraseVec.begin() == 2);
		assert(*eraseIt == 4);  // The element after the erased element
		assert(eraseVec.size() == 9);

		// Verify the contents
		std::vector<int> expectedAfterFirstErase = { 1, 2, 4, 5, 6, 7, 8, 9, 10 };
		for (size_t i = 0; i < expectedAfterFirstErase.size(); ++i) {
			assert(eraseVec[i] == expectedAfterFirstErase[i]);
		}

		// Erase range of elements
		eraseIt = eraseVec.erase(eraseVec.begin() + 1, eraseVec.begin() + 4);

		// Verify the iterator points to the correct element
		assert(eraseIt - eraseVec.begin() == 1);
		assert(*eraseIt == 6);  // The element after the erased range
		assert(eraseVec.size() == 6);

		// Verify the contents
		std::vector<int> expectedAfterRangeErase = { 1, 6, 7, 8, 9, 10 };
		for (size_t i = 0; i < expectedAfterRangeErase.size(); ++i) {
			assert(eraseVec[i] == expectedAfterRangeErase[i]);
		}
	}

	// Test erase with out of range position
	{
		Vector<int> eraseVec = { 1, 2, 3, 4, 5 };
		try {
			eraseVec.erase(eraseVec.end());
			assert(false);  // Should not reach here
		}
		catch (const std::out_of_range&) {
			std::cout << "Erase out of range test passed" << std::endl;
		}
	}

	std::cout << "Tous les tests d'erase() ont réussi !" << std::endl;
}

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
	/*std::cout << "\nFonctionnalités à ajouter :" << std::endl;
	std::cout << "1. operator= (affectation)" << std::endl;
	std::cout << "2. Constructeur de copie" << std::endl;
	std::cout << "3. Constructeur de déplacement" << std::endl;
	std::cout << "4. operator[] avec vérification des bornes" << std::endl;
	std::cout << "5. clear()" << std::endl;
	std::cout << "6. reserve()" << std::endl;
	std::cout << "7. resize()" << std::endl;
	std::cout << "8. empty()" << std::endl;
	std::cout << "9. at()" << std::endl;
	std::cout << "10. begin() et end()" << std::endl;*/

	// Nouveaux tests

	// 1. Test de l'opérateur d'affectation (operator=)
	Vector<int> vec1 = { 1, 2, 3 };
	Vector<int> vec2;
	vec2 = vec1;
	assert(vec1.size() == vec2.size());
	for (size_t i = 0; i < vec1.size(); ++i) {
		assert(vec1[i] == vec2[i]);
	}

	// 2. Test du constructeur de copie
	Vector<int> vec3(vec1);
	assert(vec1.size() == vec3.size());
	for (size_t i = 0; i < vec1.size(); ++i) {
		assert(vec1[i] == vec3[i]);
	}

	// 3. Test du constructeur de déplacement
	Vector<int> vec4(std::move(vec3));
	assert(vec4.size() == 3);
	assert(vec3.size() == 0);  // vec3 devrait être vide après le déplacement

	// 4. Test de l'opérateur[] avec vérification des bornes
	try {
		vec1[vec1.size()];  // Ceci devrait lancer une exception
		assert(false);  // Si on arrive ici, le test a échoué
	}
	catch (const std::out_of_range&) {
		// C'est le comportement attendu
		std::cout << "Test de l'opérateur[] avec vérification des bornes réussi" << std::endl;
	}

	// 5. Test de clear()
	vec1.clear();
	assert(vec1.size() == 0);
	//assert(vec1.capacity() == 0);

	// 6. Test de reserve()
	vec1.reserve(10);
	assert(vec1.capacity() >= 10);

	// 7. Test de resize()
	vec1.resize(5, 42);
	assert(vec1.size() == 5);
	for (int i : vec1) {
		assert(i == 42);
	}

	// 8. Test de empty()
	assert(vec1.empty() == false);
	Vector<int> emptyVec;
	assert(emptyVec.empty() == true);

	// 9. Test de at()
	assert(vec1.at(0) == 42);
	try {
		vec1.at(vec1.size());  // Ceci devrait lancer une exception
		assert(false);  // Si on arrive ici, le test a échoué
	}
	catch (const std::out_of_range&) {
		// C'est le comportement attendu
		std::cout << "Test de at() réussi" << std::endl;
	}

	// 10. Test de begin() et end()
	int sum = 0;
	for (auto it = vec1.begin(); it != vec1.end(); ++it) {
		sum += *it;
	}
	assert(sum == 42 * 5);

	// 1. Test insert() at different positions
	Vector<int> insertVec = { 1, 2, 3, 4, 5 };

	// Insert at the beginning
	auto it = insertVec.insert(insertVec.begin(), 0);
	assert(*it == 0);
	assert(insertVec.size() == 6);
	assert(insertVec[0] == 0);

	// Insert in the middle
	it = insertVec.insert(insertVec.begin() + 3, 10);
	assert(*it == 10);
	assert(insertVec.size() == 7);
	assert(insertVec[3] == 10);

	// Insert multiple elements
	it = insertVec.insert(insertVec.end(), 3, 7);
	assert(*it == 7);
	assert(insertVec.size() == 10);
	assert(insertVec[7] == 7);
	assert(insertVec[8] == 7);
	assert(insertVec[9] == 7);

	// Test insert with out of range position
	try {
		insertVec.insert(insertVec.end() + 1, 100);
		assert(false);  // Should not reach here
	}
	catch (const std::out_of_range&) {
		std::cout << "Insert out of range test passed" << std::endl;
	}

	// 2. Test erase() 
	Vector<int> eraseVec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// Erase 
	testErase();

	// 3. Test pop_back()
	Vector<int> popVec = { 1, 2, 3, 4, 5 };
	size_t originalSize = popVec.size();
	popVec.pop_back();
	assert(popVec.size() == originalSize - 1);
	assert(popVec.back() == 4);

	// Test pop_back() on empty vector
	try {
		Vector<int> emptyVec;
		emptyVec.pop_back();
		assert(false);  // Should not reach here
	}
	catch (const std::runtime_error&) {
		std::cout << "Pop back on empty vector test passed" << std::endl;
	}

	// 4. Test front() and back()
	Vector<int> frontBackVec = { 10, 20, 30 };
	assert(frontBackVec.front() == 10);
	assert(frontBackVec.back() == 30);

	const Vector<int>& constFrontBackVec = frontBackVec;
	assert(constFrontBackVec.front() == 10);
	assert(constFrontBackVec.back() == 30);

	// 5. Test swap()
	Vector<int> swapVec1 = { 1, 2, 3 };
	Vector<int> swapVec2 = { 4, 5, 6, 7 };

	size_t size1 = swapVec1.size();
	size_t size2 = swapVec2.size();

	swapVec1.swap(swapVec2);

	assert(swapVec1.size() == size2);
	assert(swapVec2.size() == size1);

	// 6. Test reverse iterators
	Vector<int> reverseVec = { 1, 2, 3, 4, 5 };
	int expectedReverse[] = { 5, 4, 3, 2, 1 };

	// Test reverse iterator forward traversal
	size_t index = 0;
	for (auto rit = reverseVec.rbegin(); rit != reverseVec.rend(); ++rit) {
		assert(*rit == expectedReverse[index]);
		++index;
	}

	// Test const reverse iterator
	const Vector<int>& constReverseVec = reverseVec;
	index = 0;
	for (auto rit = constReverseVec.rbegin(); rit != constReverseVec.rend(); ++rit) {
		assert(*rit == expectedReverse[index]);
		++index;
	}

	std::cout << "Tous les tests de méthodes supplémentaires ont réussi !" << std::endl;
}
int main()
{
	testVectors();
	
	
}

