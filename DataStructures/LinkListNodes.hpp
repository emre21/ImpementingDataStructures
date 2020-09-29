#pragma once

#ifndef LINKLISTNODES_HPP
#define LINKLISTNODES_HPP

#include "Node.hpp"

/*
    TODO
     ==operattor overload;

*/


template <typename T>
class LinkListNode : public Node<T> {

public:
    LinkListNode();
    LinkListNode(T value);
    LinkListNode(const LinkListNode& c_linkListNode);
    ~LinkListNode();
    LinkListNode<T>*& getNext();
    bool isLastNode();
private:
    LinkListNode<T>* m_next = nullptr;
};

template <typename T>
class DoublyLinkListNode : public Node<T> {

public:
    DoublyLinkListNode();

    DoublyLinkListNode(T value);

    DoublyLinkListNode(const DoublyLinkListNode&
        c_doubleLinkListNode);

    ~DoublyLinkListNode();

    DoublyLinkListNode<T>*& getNext();

    DoublyLinkListNode<T>*& getBack();

private:
    DoublyLinkListNode<T>* m_nextNode = nullptr;
    DoublyLinkListNode<T>* m_backNode = nullptr;
};


#include "LinkListNodes.hpp"
template <typename T>
LinkListNode<T>::LinkListNode()
    :Node()
{

}

template <typename T>
LinkListNode<T>::LinkListNode(T value)
    :Node(value)
{

}

template <typename T>
LinkListNode<T>::LinkListNode(const LinkListNode& c_linkListNode)
    :Node(c_linkListNode)
{
    this->m_next = c_linkListNode.getNext();
}

template <typename T>
LinkListNode<T>::~LinkListNode() {
    
}

template <typename T>
LinkListNode<T>*& LinkListNode<T>::getNext()
{
    return m_next;
}

template <typename T>
bool LinkListNode<T>::isLastNode()
{
    return m_next == nullptr ? true : false;
}

/***** DOUBLY LINK LIST IMPL *****/

template <typename T>
DoublyLinkListNode<T>::DoublyLinkListNode()
    : Node()
{

}

template <typename T>
DoublyLinkListNode<T>::DoublyLinkListNode(T value)
    : Node(value)
{

}


template <typename T>
DoublyLinkListNode<T>::DoublyLinkListNode(const DoublyLinkListNode& c_doublyLinkListNode)
    : Node(c_doublyLinkListNode)
{
    this->m_nextNode = c_doublyLinkListNode.getNext();
    this->m_backNode = c_doublyLinkListNode.getBack();
}

template <typename T>
DoublyLinkListNode<T>::~DoublyLinkListNode()
{

}
template <typename T>
DoublyLinkListNode<T>*& DoublyLinkListNode<T>::getNext()
{
    return m_nextNode;
}

template <typename T>
DoublyLinkListNode<T>*& DoublyLinkListNode<T>::getBack()
{
    return m_backNode;
}



#endif