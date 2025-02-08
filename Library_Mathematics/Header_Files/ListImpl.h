#ifndef MY_LIST_H
#error Do not include this header directly. Please include ListImpl.h
#endif
namespace Mathematical_library
{
	template<typename T>
	List<T>::List()
		: m_first(nullptr), m_last(nullptr)
	{
	}

	template<typename T>
	List<T>::List(const List& other) : m_first(nullptr), m_last(nullptr)
	{
		for (const auto& value : other)
		{
			push_back(value);
		}
	}

	template<typename T>
	List<T>::List(List&& other) noexcept
		: m_first(other.m_first), m_last(other.m_last)
	{
		other.m_first = other.m_last = nullptr;
	}

	template<typename T>
	List<T>::List(std::initializer_list<T> init) : m_first(nullptr), m_last(nullptr)
	{
		for (const auto& value : init)
		{
			push_back(value);
		}
	}

	template<typename T>
	List<T>::List(size_t count, const T& value) : m_first(nullptr), m_last(nullptr)
	{
		for (size_t i = 0; i < count; ++i)
		{
			push_back(value);
		}
	}

	template<typename T>
	template<typename InputIt>
	List<T>::List(InputIt first, InputIt last) : m_first(nullptr), m_last(nullptr)
	{
		for (auto it = first; it != last; ++it)
		{
			push_back(*it);
		}
	}


	template<typename T>
	List<T>::~List()
	{
		clear();
	}

	// Opérateurs d'affectation
	template<typename T>
	List<T>& List<T>::operator=(const List& other)
	{
		if (this != &other)
		{
			List tmp(other);
			swap(tmp);
		}
		return *this;
	}

	template<typename T>
	List<T>& List<T>::operator=(List&& other) noexcept
	{
		if (this != &other)
		{
			clear();
			m_first = other.m_first;
			m_last = other.m_last;
			other.m_first = other.m_last = nullptr;
		}
		return *this;
	}

	template<typename T>
	List<T>& List<T>::operator=(std::initializer_list<T> list)
	{
		List tmp(list);
		swap(tmp);
		return *this;
	}


	template<typename T>
	bool List<T>::empty() const
	{
		return m_first == nullptr;
	}
	template<typename T>
	size_t List<T>::size() const
	{
		size_t count = 0;
		Node* current = m_first;


		while (current != nullptr)
		{
			count++;
			current = current->next;
		}

		return count;
	}

	template<typename T>
	void List<T>::clear()
	{
		while (!empty())
		{
			pop_front();
		}
	}

	// Accès aux éléments
	template<typename T>
	T& List<T>::front()
	{
		if (empty()) throw std::out_of_range("List is empty");
		return m_first->value;
	}

	template<typename T>
	const T& List<T>::front() const
	{
		if (empty()) throw std::out_of_range("List is empty");
		return m_first->value;
	}

	template<typename T>
	T& List<T>::back()
	{
		if (empty()) throw std::out_of_range("List is empty");
		return m_last->value;
	}

	template<typename T>
	const T& List<T>::back() const
	{
		if (empty()) throw std::out_of_range("List is empty");
		return m_last->value;
	}


	template<typename T>
	void List<T>::push_back(const T& elem)
	{
		Node* newNode = new Node(elem);
		if (empty())
		{
			m_first = m_last = newNode;
		}
		else
		{
			newNode->previous = m_last;
			m_last->next = newNode;
			m_last = newNode;
		}
	}

	template<typename T>
	void List<T>::push_front(const T& elem)
	{
		Node* newNode = new Node(elem);
		if (empty())
		{
			m_first = m_last = newNode;
		}
		else
		{
			newNode->next = m_first;
			m_first->previous = newNode;
			m_first = newNode;
		}
	}

	template<typename T>
	void List<T>::pop_back()
	{
		if (empty()) return;

		if (m_first == m_last)
		{
			delete m_last;
			m_first = m_last = nullptr;
		}
		else
		{
			Node* oldLast = m_last;
			m_last = m_last->previous;
			m_last->next = nullptr;
			delete oldLast;
		}
	}

	template<typename T>
	void List<T>::pop_front()
	{
		if (empty()) return;

		if (m_first == m_last)
		{
			delete m_first;
			m_first = m_last = nullptr;
		}
		else
		{
			Node* oldFirst = m_first;
			m_first = m_first->next;
			m_first->previous = nullptr;
			delete oldFirst;
		}
	}


	// Insert un seul élément
	template<typename T>
	typename List<T>::iterator List<T>::insert(const_iterator pos, const T& value)
	{
		Node* newNode = new Node(value);

		// Si la liste est vide ou on insère à la fin
		if (pos.m_ptr == nullptr || empty())
		{
			if (empty())
			{
				m_first = m_last = newNode;
			}
			else
			{
				newNode->previous = m_last;
				m_last->next = newNode;
				m_last = newNode;
			}
			return iterator(newNode);
		}

		// Si on insère au début de la liste
		if (pos.m_ptr == m_first)
		{
			newNode->next = m_first;
			m_first->previous = newNode;
			m_first = newNode;
			return iterator(newNode);
		}

		// Insertion au milieu de la liste
		Node* nextNode = pos.m_ptr;
		Node* prevNode = nextNode->previous;

		newNode->next = nextNode;
		newNode->previous = prevNode;
		nextNode->previous = newNode;
		prevNode->next = newNode;

		return iterator(newNode);
	}

	// Insert n copies d'un élément
	template<typename T>
	typename List<T>::iterator List<T>::insert(const_iterator pos, size_t count, const T& value)
	{
		if (count == 0)
			return iterator(pos.m_ptr);

		// Garder la position du premier élément inséré pour le retourner
		iterator firstInserted = insert(pos, value);

		// Insérer les éléments restants
		for (size_t i = 1; i < count; ++i)
		{
			insert(pos, value);
		}

		return firstInserted;
	}

	// Insert une plage d'éléments
	template<typename T>
	template<typename InputIt>
	typename List<T>::iterator List<T>::insert(const_iterator pos, InputIt first, InputIt last)
	{
		// Vérification préliminaire
		if (first == last)
			return iterator(pos.m_ptr);

		// Utiliser enable_if pour s'assurer que la méthode n'est pas confondue avec les autres overloads
		// et qu'elle n'est pas utilisée avec des types intégraux
		static_assert(!std::is_integral<InputIt>::value,
			"This overload must not be selected for integral types");

		// Stocker les éléments dans un vecteur
		Vector<T> elements;
		for (auto it = first; it != last; ++it) {
			elements.push_back(*it);
		}

		// Insérer les éléments dans l'ordre correct
		iterator result;
		for (auto it = elements.rbegin(); it != elements.rend(); ++it)
		{
			result = insert(pos, *it);
		}

		return result;
	}

	// Insert avec liste d'initialisation
	template<typename T>
	typename List<T>::iterator List<T>::insert(const_iterator pos, std::initializer_list<T> ilist)
	{
		if (ilist.size() == 0)
			return iterator(pos.m_ptr);

		// Utiliser votre Vector pour stocker la liste d'initialisation
		Vector<T> elements(ilist);

		// Insérer les éléments dans l'ordre correct
		iterator result;
		for (auto it = elements.rbegin(); it != elements.rend(); ++it)
		{
			result = insert(pos, *it);
		}

		return result;
	}

	template<typename T>
	typename List<T>::iterator List<T>::erase(const_iterator pos)
	{
		if (pos.m_ptr == nullptr || empty())
			return end();

		Node* nodeToDelete = pos.m_ptr;
		Node* nextNode = nodeToDelete->next;
		Node* prevNode = nodeToDelete->previous;

		// Cas spécial : supprimer le premier élément
		if (nodeToDelete == m_first)
		{
			m_first = nextNode;
		}

		// Cas spécial : supprimer le dernier élément
		if (nodeToDelete == m_last)
		{
			m_last = prevNode;
		}

		// Mettre à jour les liens
		if (prevNode)
		{
			prevNode->next = nextNode;
		}
		if (nextNode)
		{
			nextNode->previous = prevNode;
		}

		// Si c'était le seul élément
		if (nodeToDelete == m_first && nodeToDelete == m_last)
		{
			m_first = m_last = nullptr;
		}

		delete nodeToDelete;
		return iterator(nextNode);
	}

	template<typename T>
	typename List<T>::iterator List<T>::erase(const_iterator first, const_iterator last)
	{
		if (first == last)
			return iterator(last.m_ptr);

		while (first.m_ptr != last.m_ptr)
		{
			first = erase(first);
		}
		return iterator(last.m_ptr);
	}

	template<typename T>
	void List<T>::swap(List& other) noexcept
	{
		std::swap(m_first, other.m_first);
		std::swap(m_last, other.m_last);
	}

	template<typename T>
	void List<T>::resize(size_t count)
	{
		resize(count, T());
	}

	template<typename T>
	void List<T>::resize(size_t count, const T& value)
	{
		size_t currentSize = size();
		if (count < currentSize)
		{
			while (size() > count)
			{
				pop_back();
			}
		}
		else if (count > currentSize) {

			while (size() < count)
			{
				push_back(value);
			}
		}
	}

	template<typename T>
	bool List<T>::operator==(const List& other) const
	{
		Node* current1 = this->m_first;
		Node* current2 = other.m_first;

		while (current1 != nullptr && current2 != nullptr)
		{
			if (current1->value != current2->value)
			{
				return false;
			}
			current1 = current1->next;
			current2 = current2->next;
		}
		return (current1 == nullptr && current2 == nullptr);
	}

	template<typename T>
	bool List<T>::operator!=(const List& other) const { return !(*this == other); }

	template<typename T>
	bool List<T>::operator<(const List& other) const
	{
		Node* current1 = this->m_first;
		Node* current2 = other.m_first;

		while (current1 != nullptr && current2 != nullptr) {
			if (current1->value < current2->value) {
				return true;
			}
			if (current1->value > current2->value) {
				return false;
			}
			current1 = current1->next;
			current2 = current2->next;
		}

		return (current1 == nullptr && current2 != nullptr);
	}

	template<typename T>
	bool List<T>::operator>(const List& other) const { return other < *this; }

	template<typename T >
	bool List<T>::operator<=(const List& other) const { return !(other < *this); }

	template<typename T>
	bool List<T>::operator>=(const List& other) const { return !(*this < other); }
}