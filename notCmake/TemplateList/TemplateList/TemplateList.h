#ifndef MY_TEMPLATE_LIST_H
#define MY_TEMPLATE_LIST_H
template<typename T>
class List
{
public:
    List();
    ~List();

    void push_back(const T& elem);

    void push_front(const T& elem);

    void pop_back();
    

    void pop_front();

    const T& back() const;

    const T& front() const;

    size_t size() const;

private:
    struct Node;

    Node* m_first;
    Node* m_last;
};
#endif

#include "TemplateListImpl.h"