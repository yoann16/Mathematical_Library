#ifndef MY_TEMPLATE_LIST_H
#error Do not include this header directly. Please include TemplateList.h
#endif
template<typename T>
struct List<T>::Node
{
    Node(const T& value_) : value(value_), previous(nullptr), next(nullptr) {}
    T value;
    Node* previous;
    Node* next;
};

template<typename T>
List<T>::List() : m_first(nullptr), m_last(nullptr)
{
}
template<typename T>
List<T>::~List()
{
    Node* ptr = m_first;
    while (ptr != nullptr)
    {
        Node* nextPtr = ptr->next;
        delete ptr;
        ptr = nextPtr;
    }
}
template<typename T>
void List<T>::push_back(const T& elem)
{
    Node* newNode = new Node{ elem };
    newNode->next = nullptr;
    if (m_last == nullptr)
    {
        m_last = newNode;
        m_first = newNode;
        newNode->previous = nullptr;
    }
    else
    {
        m_last->next = newNode;
        newNode->previous = m_last;
        m_last = newNode;
    }
}
template<typename T>
void List<T>::push_front(const T& elem)
{
    Node* newNode = new Node{ elem };
    newNode->previous = nullptr;
    if (m_first == nullptr)
    {
        m_last = newNode;
        m_first = newNode;
        newNode->next = nullptr;
    }
    else
    {
        m_first->previous = newNode;
        newNode->next = m_first;
        m_first = newNode;
    }
}
template<typename T>
void List<T>::pop_back()
{
    if (m_first == m_last)
    {
        delete m_last;
        m_first = nullptr;
        m_last = nullptr;
    }
    else
    {
        m_last->previous->next = nullptr;
        Node* formerLast = m_last;
        m_last = m_last->previous;
        delete formerLast;

    }
}
template<typename T>
void List<T>::pop_front()
{
    if (m_first == m_last)
    {
        delete m_first;
        m_first = nullptr;
        m_last = nullptr;
    }
    else
    {
        m_first->next->previous = nullptr;
        Node* formerFirst = m_first;
        m_first = m_first->next;
        delete formerFirst;
    }
}
template<typename T>
const T& List<T>::back() const
{
    return m_last->value;
}
template<typename T>
const T& List<T>::front() const
{
    return m_first->value;
}
template<typename T>
size_t List<T>::size() const
{
    size_t size = 0;
    Node* ptr = m_first;
    while (ptr != nullptr)
    {
        ptr = ptr->next;
        size++;
    }

    return size;
}
template class List<int>;
template class List<size_t>;