#pragma once
#ifndef NODE_HPP
#define NODE_HPP

#include <type_traits>


template <typename T>
class Node {

public:
    Node();
    Node(T value);
    Node(const Node& c_Node);
    T& getValue();
    void setValue(T value);
    Node<T>& operator=(const Node& Node1);
    ~Node();
private:
    T m_value;
};



template<typename T>
Node<T>::Node() {

}

template<typename T>
Node<T>::Node(T value) {
    m_value = value;
}

template <typename T>
Node<T>::Node(const Node<T>& c_Node) {
    this->m_value = c_Node.getValue();
}

template <typename T>
T& Node<T>::getValue() {

    return m_value;

}

template <typename T>
void Node<T>::setValue(T value) {
    value = value;
}

template <typename T>
Node<T>& Node<T>::operator=(const Node<T>& node1)
{
    if constexpr (this == nullptr)
    {
        this = new Node<T>(node1.getValue());
    }
    else {
        this->setValue(node1.getValue);
    }

    return this;
}
template <typename T>
Node<T>::~Node() {

}

#endif