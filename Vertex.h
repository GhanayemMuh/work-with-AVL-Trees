//
// Created by Muhammad Ghanayem on 20/04/2022.
//

#ifndef VERTEX_H_
#define VERTEX_H_
#include <iostream>


template<class T>
class Vertex {
    Vertex* left;
    Vertex* right;
    T value;
    int height;
public:
    explicit Vertex(const T& value);
    ~Vertex() = default;
    Vertex* getLeft() const;
    Vertex* getRight() const;
    T& getValue();
    int getHeight() const;
    void setLeft(Vertex* vertex);
    void setRight(Vertex* vertex);
    void setValue(const T& value1);
    void setHeight(int height1);
};

template<class T>
Vertex<T>::Vertex(const T &value):left(nullptr),right(nullptr),value(value),height(0) {}

template<class T>
Vertex<T> *Vertex<T>::getLeft() const
{
    if (!this)
    {
        return nullptr;
    }
    return this->left;
}

template<class T>
Vertex<T> *Vertex<T>::getRight() const
{
    if (!this)
    {
        return nullptr;
    }
    return this->right;
}

template<class T>
T &Vertex<T>::getValue()
{
    return this->value;
}

template<class T>
int Vertex<T>::getHeight() const
{
    if (!this)
    {
        return -1;
    }
    return this->height;
}

template<class T>
void Vertex<T>::setLeft(Vertex<T> *vertex)
{
    if (!this)
    {
        return;
    }
    this->left = vertex;
}

template<class T>
void Vertex<T>::setRight(Vertex<T> *vertex)
{
    if (!this)
    {
        return;
    }
    this->right = vertex;
}

template<class T>
void Vertex<T>::setValue(const T &value1)
{
    if (!this)
    {
        return;
    }
    this->value = value1;
}

template<class T>
void Vertex<T>::setHeight(int height1)
{
    if (!this)
    {
        return;
    }
    this->height = height1;
}

#endif //VERTEX_H_
