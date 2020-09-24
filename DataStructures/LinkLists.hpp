#pragma once
#ifndef LINKLISTS_HPP
#define LINKLISTS_HPP

#include <utility>
#include <functional>

#include "has_operator.hpp"
#include "LinkListNodes.hpp"

/*
    TODO
        * write circularLinkList from intheritance LinkList
        * wirte CircularLÝnkList::addByIndex index > size control
        * wirte CircularLÝnkList::addByIndex add lastElement Feature
*/


template <typename T>
class ILinkList {

public:
    virtual void add(T) = 0;
    virtual void addByIndex(int, T) = 0;
    virtual T& getElementByIndex(int) = 0;
    virtual void deleteElementByIndex(int) = 0;
    virtual void deleteElement(T) = 0;
    virtual int getSize() = 0;
    virtual T& getRoot() = 0;

};

template <typename T>
class LinkList : public ILinkList<T> {

public:
    LinkList();
    LinkList(T value);
    void add(T value);
    void addByIndex(int index, T value);
    T& getElementByIndex(int index);
    void deleteElementByIndex(int index);
    void deleteElement(T value, std::function<bool(T, T)> compareFunc);
    void deleteElement(T value);
    int getSize();
    T& getRoot();

protected:
    LinkListNode<T>* m_rootNodePtr;
    LinkListNode<T>* m_lastNodePtr;
    int m_size = 0;

    LinkListNode<T>& getNodeByIndex(int index);
    std::pair<bool, int> findValueIndex(T value, std::function<bool(T, T)> compareFunc = 0);
    std::pair<bool, int> findValueIndex(T value);

    inline void updateLastNodePtr(LinkListNode<T>&& t_lastNodePtr);
};

template <typename T>
class DoublyLinkList : ILinkList<T> {

public:
    DoublyLinkList();
    DoublyLinkList(T value);
    void add(T value);
    void addByIndex(int index, T value);
    T getElementByIndex(int index);
    void deleteElementByIndex(int index);
    void deleteElement(T value, std::function<bool(T, T)> compareFunc);
    void deleteElement(T value);
    int getSize();
    T& getRoot();
private:
    DoublyLinkListNode<T>* m_rootNodePtr = nullptr;
    DoublyLinkListNode<T>* m_lastNodePtr = nullptr;
    int m_size = 0;

    DoublyLinkListNode<T>& getNodeByIndex(int index);
    std::pair<bool, int> findValueIndex(T value, std::function<bool(T, T)> compareFunc);
    std::pair<bool, int> findValueIndex(T value);
    void updateLastNodePtr(DoublyLinkListNode<T>&& t_lastNodePtr);
};

template <typename T>
class CircularLinkList : ILinkList<T> {

public:
    CircularLinkList();
    CircularLinkList(T value);
    void add(T value);
    void addByIndex(int index, T value);
    T getElementByIndex(int index);
    void deleteElementByIndex(int index);
    void deleteElement(T value);
    void deleteElement(T value, std::function<bool(T, T)> compareFunc);
    int getSize();
    T& getRoot();

private:

    LinkListNode<T>* m_rootNodePtr;
    LinkListNode<T>* m_lastNodePtr;

    void updateLastNodePtr(LinkListNode<T>&& t_lastNodePtr);
    LinkListNode<T>& getNodeByIndex(int index);
    std::pair<bool, int> findValueIndex(T value, std::function<bool(T, T)> compareFunc = 0);
    std::pair<bool, int> findValueIndex(T value);

    // root un back i zaten lastNode
    int m_size = 0;
};



template <typename T>
LinkList<T>::LinkList()
{
    m_rootNodePtr = nullptr;
    m_lastNodePtr = nullptr;
    m_size = 0;
}

template <typename T>
LinkList<T>::LinkList(T value)
{
    m_rootNodePtr = new LinkListNode<T>(value);
    m_size++;
    updateLastNodePtr(m_rootNodePtr);
}

template <typename T>
void LinkList<T>::add(T value)
{
    m_lastNodePtr->getNext() = new LinkListNode<T>(value);
    updateLastNodePtr(m_lastNodePtr->getNext());
    m_size++;
}

template <typename T>
void LinkList<T>::addByIndex(int index, T value) {

    static_assert(index > m_size, "Index error");

    auto& prevNode = getNodeByIndex(index);

    auto& nextNode = prevNode.getNextNode();

    prevNode.getNext() = new LinkListNode(value);
    prevNode.getNext().getNext() = nextNode;

    // last NOde update is required 
}

template <typename T>
T& LinkList<T>::getElementByIndex(int index)
{
    static_assert(index > m_size, "Index error");

    return getNodeByIndex(index).getValue();
}

template <typename T>
void LinkList<T>::deleteElementByIndex(int index)
{
    auto& prevNode = getNodeByIndex(index - 1);

    auto& nextNode = prevNode.getNext().getNext();

    delete prevNode.getNext();

    prevNode.getNext() = nextNode;
}



template <typename T>
void LinkList<T>::deleteElement(T value)
{

    static_assert(has_equal<T>::value, "! ERROR :: Template parameter dont has {operator==}  ");

    auto [find, index] = findValueIndex(value);
    if (find == true)
    {
        deleteElementByIndex(index);
    }
    else
    {

        std::cerr << "Dont found " <<
            value
            << "in the list \n";

    }
}


template <typename T>
void LinkList<T>::deleteElement(T value, std::function<bool(T, T)> compareFunc)
{


    auto [find, index] = findValueIndex(value, compareFunc);
    if (find != true)
    {
        deleteElementByIndex(index);
    }
    else
    {

        std::cerr << "Dont found " <<
            value
            << "in the list \n";

    }
}


template <typename T>
int LinkList<T>::getSize() {
    return m_size;
}

template <typename T>
T& LinkList<T>::getRoot() {
    return m_rootNodePtr;
}

template <typename T>
LinkListNode<T>& LinkList<T>::getNodeByIndex(int index) {

    LinkListNode<T>* tempRoot = m_rootNodePtr;
    for (int i = 0; i < index; ++i)
    {
        tempRoot = tempRoot->getNext();
    }

    return tempRoot;
}

template <typename T>
std::pair<bool, int> LinkList<T>::findValueIndex(T value) {

    LinkListNode<T>* tempNode = m_rootNodePtr;

    int index = 0;
    bool found = true;
    while (tempNode->getValue() != value)
    {
        index++;

        if (tempNode->getNext() == nullptr)
        {
            found = false;
            break;

        }

        tempNode = tempNode->getNext();

    }

    return std::pair<bool, int>{found, index};
}


template <typename T>
std::pair<bool, int> LinkList<T>::findValueIndex(T value,
    std::function<bool(T, T)> compareFunc)
{

    LinkListNode<T>* tempNode = m_rootNodePtr;
    int index = 0;
    bool found = true;

    while (compare_func(tempNode->getValue(), value) != true)
    {
        index++;

        if (tempNode->getNext() == nullptr)
        {
            found = false;
            break;

        }
    }

    return std::pair<bool, int>{found, index};
}


template <typename T>
inline void LinkList<T>::updateLastNodePtr(LinkListNode<T>&& t_lastNodePtr)
{
    m_lastNodePtr = t_lastNodePtr;
}

/******************************************/
/******************************************/
/******** DOUBLY LINK LÝST IMPL  **********/
/******************************************/
/******************************************/

template <typename T>
DoublyLinkList<T>::DoublyLinkList()
{

}

template <typename T>
DoublyLinkList<T>::DoublyLinkList(T value)
{
    m_rootNodePtr = new DoublyLinkListNode(value);
    m_size++;
    updateLastNodePtr(m_rootNodePtr);
}

template <typename T>
void DoublyLinkList<T>::add(T value) {
    auto& addingNode = m_lastNodePtr->getNext();
    addingNode = new DoublyLinkListNode<T>(value);
    addingNode.getBack() = *m_lastNodePtr;
    updateLastNodePtr(&addingNode);
    m_size++;
}

template <typename T>
void DoublyLinkList<T>::addByIndex(int index, T value)
{
    // need static assert

    auto& prevNode = getNodeByIndex(index - 1);
    auto& tempNextNode = prevNode.getNext();
    DoublyLinkListNode<T> addingNode(value);
    prevNode.getNext() = addingNode;
    addingNode.getBack() = prevNode;
    tempNextNode.getBack() = addingNode;
    m_size++;

}

template <typename T>
T DoublyLinkList<T>::getElementByIndex(int index)
{
    // need static assert
    return getNodeByIndex(index).getValue();
}


template <typename T>
void DoublyLinkList<T>::deleteElementByIndex(int index)
{
    // need static_asser
    auto& deletingNode = getNodeByIndex(index);
    if (deletingNode.getNext() != nullptr)
    {
        deletingNode.getBack() = deletingNode.getnext();
    }

    else {
        updateLastNodePtr(deletingNode.getback());
    }

    delete deletingNode;
    m_size--;

}

template <typename T>
void DoublyLinkList<T>::deleteElement(T value)
{
    // size update;

    static_assert(has_equal<T>::value, "! ERROR :: Template parameter dont has {operator==}  ");

    auto [find, index] = findValueIndex(value);

    if (find == true)
    {
        deleteElementByIndex(index);
    }
    else
    {
        std::cerr << "Dont found " <<
            value
            << "in the list \n";

    }

}

template <typename T>
void DoublyLinkList<T>::deleteElement(T value,
    std::function<bool(T, T)> compareFunc)
{

    auto [find, index] = findValueIndex(value, compareFunc);


    if (find == true)
    {
        deleteElementByIndex(index);
    }
    else
    {
        std::cerr << "Dont found " <<
            value
            << "in the list \n";

    }
}


template <typename T>
int DoublyLinkList<T>::getSize() {
    return m_size;
}

template <typename T>
T& DoublyLinkList<T>::getRoot() {
    return m_rootNodePtr;
}

template <typename T>
DoublyLinkListNode<T>& DoublyLinkList<T>::getNodeByIndex(int index) {

    DoublyLinkListNode<T>* temp_root_ptr = m_rootNodePtr;

    for (int i = 0; i < index; ++i)
    {
        temp_root_ptr = temp_root_ptr->getNext();
    }

    return temp_root_ptr;
}

template <typename T>
std::pair<bool, int> DoublyLinkList<T>::findValueIndex(T value,
    std::function<bool(T, T)> compareFunc)
{
    DoublyLinkListNode<T>* tempNode = m_rootNodePtr;
    bool found = false;
    int index = 0;
    while (compareFunc(tempNode.getValue(), value) != true)
    {

        index++;

        if (tempNode.getNext() == nullptr)
        {
            found = false;
            break;

        }
    }
}

template <typename T>
std::pair<bool, int> DoublyLinkList<T>::findValueIndex(T value)
{
    DoublyLinkListNode<T>* tempNode = m_rootNodePtr;
    bool found = false;
    int index = 0;
    while (!tempNode->getValue() == value)
    {

        index++;

        if (tempNode.getNext() == nullptr)
        {
            found = false;
            break;

        }

        tempNode = tempNode->getNext();
    }

    return std::pair<bool, int>{found, index};

}



template <typename T>
void DoublyLinkList<T>::updateLastNodePtr(DoublyLinkListNode<T>&& t_lastNodePtr)
{

    m_lastNodePtr = t_lastNodePtr;
}

/******************************************/
/******************************************/
/******* CIRCULAR LINK LÝST IMPL  *********/
/******************************************/
/******************************************/



template<typename T>
CircularLinkList<T>::CircularLinkList() {
    m_rootNodePtr = nullptr;
}

template<typename T>
CircularLinkList<T>::CircularLinkList(T value) {
    m_rootNodePtr = new LinkListNode<T>(value);
    m_size++;
}

template<typename T>
void CircularLinkList<T>::add(T value) {
    if (m_rootNodePtr == nullptr)
    {
        m_rootNodePtr = new LinkListNode<T>(value);
        m_lastNodePtr = m_rootNodePtr;
    }
    else
    {
        LinkListNode<T>* tempRoot = m_rootNodePtr;
        m_lastNodePtr->getNext() = new LinkListNode<T>(value);
        m_lastNodePtr->getNext()->getNext() = tempRoot;
        updateLastNodePtr(m_lastNodePtr->getNext());

    }

    m_size++;

}

template <typename T>
void CircularLinkList<T>::addByIndex(int index, T value) {



    if (index != 0)
    {
        LinkListNode<T>* prevNode = getNodeByIndex(index - 1);
    }
    else
    {
        LinkListNode<T>* addingNode = new LinkListNode(value);
        m_lastNodePtr->getNext() = addingNode;
        addingNode->getNext() = m_rootNodePtr;
        m_rootNodePtr = addingNode;
    }

    m_size++;
}


template <typename T>
T CircularLinkList<T>::getElementByIndex(int index) {

    if (index >= m_size)
    {
        throw std::cerr << "EROOR index >= CircularLinkList<T>::m_size ";
    }
    else
    {
        LinkListNode<T>* tempNode = m_rootNodePtr;
        for (int i = 0; i < index; ++i)
        {
            tempNode = tempNode->getNext();
        }

        return tempNode->getValue();
    }
}

template <typename T>
void CircularLinkList<T>::deleteElementByIndex(int index) {

    if (index >= m_size)
    {
        throw std::cerr << "EROOR index >= CircularLinkList<T>::m_size ";
    }
    else
    {
        // need index control if root
        LinkListNode<T>* prevNode = getNodeByIndex(index - 1);
        LinkListNode<T>* nextNode = prevNode->getNext()->getNext();
        delete prevNode->getNext();
        prevNode->getNext() = nextNode;

        m_size--;
    }
}

template <typename T>
void CircularLinkList<T>::deleteElement(T value) {

    static_assert(has_equal<T>::value,
        "! ERROR Template parameter dont have == operand");

    auto [find, index] = findValueIndex(value);

    if (find == true)
    {
        deleteElementByIndex(index);
    }
    else
    {
        std::cerr << "Dont found " <<
            value
            << "in the list \n";

    }

}

template <typename T>
void CircularLinkList<T>::deleteElement(T value, std::function<bool(T, T)> compareFunc) {

    auto [find, index] = findValueIndex(value, compareFunc);

    if (find == true)
    {
        deleteElementByIndex(index);
    }
    else
    {
        std::cerr << "Dont found " <<
            value
            << "in the list \n";

    }

}

template <typename T>
int CircularLinkList<T>::getSize()
{
    return m_size;
}

template <typename T>
T& CircularLinkList<T>::getRoot() {
    return m_rootNodePtr->getvalue();
}

template <typename T>
void CircularLinkList<T>::updateLastNodePtr(LinkListNode<T>&& t_lastNodePtr)
{
    m_lastNodePtr = t_lastNodePtr;
    m_lastNodePtr->getNext() = m_rootNodePtr;
}

template<typename T>
LinkListNode<T>& CircularLinkList<T>::getNodeByIndex(int index)
{
    int index = 0;
    LinkListNode<T>* tempNode = m_rootNodePtr;
    for (int i = 0; i < index; ++i)
    {
        tempNode = tempNode->getNext();

    }

    return tempNode;
}

template <typename T>
std::pair<bool, int> CircularLinkList<T>::findValueIndex(T value,
    std::function<bool(T, T)> compareFunc)
{
    LinkListNode<T>* tempNode = m_rootNodePtr;
    bool find = false;
    int index = 0;
    while (compareFunc(tempNode->getValue(), value) == false)
    {

        index++;

        if (tempNode.getNext() == nullptr)
        {
            find = false;
            break;

        }

        tempNode = tempNode->getNext();
    }

    return std::pair<bool, int>{find, index};
}

template <typename T>
std::pair<bool, int> CircularLinkList<T>::findValueIndex(T value)
{
    LinkListNode<T>* tempNode = m_rootNodePtr;
    bool find = false;
    int index = 0;
    while (!tempNode->getValue() == value)
    {

        index++;

        if (tempNode.getNext() == nullptr)
        {
            find = false;
            break;

        }

        tempNode = tempNode->getNext();
    }

    return std::pair<bool, int>{find, index};
}


#endif