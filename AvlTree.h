//
// Created by Muhammad Ghanayem on 20/04/2022.
//

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <iostream>
#include <memory>
#include "Vertex.h"

class Failure : public std::exception {};

template<class T>
class AvlTree {
    Vertex<T>* root;
    Vertex<T>* max;
    int size;
public:
    AvlTree();
    ~AvlTree();
    AvlTree(const AvlTree& other) = default;
    AvlTree& operator=(const AvlTree& other) = default;
    Vertex<T>* getRoot() const;
    Vertex<T>* getMax() const;
    int getSize() const;
    void insert(const T& value);
    void remove(const T& value);
    static std::shared_ptr<AvlTree<T>> mergeTrees(const AvlTree<T>& t1,const AvlTree<T>& t2);
    T* getPtrValue(const T& value);
    void changeField(int value,Vertex<T>* vertex,void(*func)(T&,int));
    void storeReverseInorder(Vertex<T>* vertex,int* array,int* index,int number,void (*func)(const T&,int*,int*));
    void storeInorder(Vertex<T>* vertex,int* array,int* index,int number,void (*func)(const T&,int*,int*));
    void countWithinCondition(Vertex<T>* vertex,int *total_num, int *num,const T& min_val,const T& max_val,
                              int a, int b, void (*func)(const T &, int, int, int *, int *));
};

template<class T>
AvlTree<T>::AvlTree() :root(nullptr),max(nullptr),size(0) {}

template<class T>
static void clear(Vertex<T> *vertex)
{
    if (vertex)
    {
        clear(vertex->getLeft());
        clear(vertex->getRight());
        delete vertex;
    }
}

template<class T>
AvlTree<T>::~AvlTree<T>()
{
    if (root)
    {
        clear(root);
    }
    root = nullptr;
    max = nullptr;
}

template<class T>
Vertex<T> *AvlTree<T>::getRoot() const
{
    if (!this || !root)
    {
        return nullptr;
    }
    return root;
}

template<class T>
Vertex<T> *AvlTree<T>::getMax() const
{
    if (!this || !root)
    {
        return nullptr;
    }
    return max;
}

template<class T>
int AvlTree<T>::getSize() const
{
    if (!this || !root)
    {
        return 0;
    }
    return size;
}

static int getMaxInt(int x, int y)
{
    return (x >= y) ? x : y;
}

template<class T>
static Vertex<T>* rotateRight(Vertex<T> *vertex)
{
    Vertex<T>* left = vertex->getLeft();
    vertex->setLeft(left->getRight());
    vertex->setHeight(getMaxInt(vertex->getLeft()->getHeight(),vertex->getRight()->getHeight())+1);
    left->setRight(vertex);
    left->setHeight(getMaxInt(left->getLeft()->getHeight(),left->getRight()->getHeight())+1);
    return left;
}

template<class T>
static Vertex<T>* rotateLeft(Vertex<T> *vertex)
{
    Vertex<T>* right = vertex->getRight();
    vertex->setRight(right->getLeft());
    vertex->setHeight(getMaxInt(vertex->getLeft()->getHeight(),vertex->getRight()->getHeight()) + 1);
    right->setLeft(vertex);
    right->setHeight(getMaxInt(right->getLeft()->getHeight(),right->getRight()->getHeight())+1);
    return right;
}

template<class T>
static Vertex<T>* RR(Vertex<T>* vertex)
{
    return rotateLeft(vertex);
}

template<class T>
static Vertex<T>* RL(Vertex<T>* vertex)
{
    vertex->setRight(rotateRight(vertex->getRight()));
    return rotateLeft(vertex);
}

template<class T>
static Vertex<T>* LR(Vertex<T>* vertex)
{
    vertex->setLeft(rotateLeft(vertex->getLeft()));
    return rotateRight(vertex);
}

template<class T>
static Vertex<T>* LL(Vertex<T>* vertex)
{
    return rotateRight(vertex);
}


template<class T>
static int getBalanceFactor(const Vertex<T> *vertex)
{
    if (vertex)
    {
        return (vertex->getLeft()->getHeight() - vertex->getRight()->getHeight());
    }
    return 0;
}

template<class T>
static Vertex<T>* balance(Vertex<T>* vertex)
{
    if (getBalanceFactor(vertex) < -1 && getBalanceFactor(vertex->getRight()) <= 0)
    {
        return RR(vertex);
    }
    if (getBalanceFactor(vertex) < -1 && getBalanceFactor(vertex->getRight()) > 0)
    {
        return RL(vertex);
    }
    if (getBalanceFactor(vertex) > 1 && getBalanceFactor(vertex->getLeft()) < 0)
    {
        return LR(vertex);
    }
    if (getBalanceFactor(vertex) > 1 && getBalanceFactor(vertex->getLeft()) >= 0)
    {
        return LL(vertex);
    }
    return vertex;
}

template<class T>
static Vertex<T>* insertAndBalance(Vertex<T> *vertex, Vertex<T> *to_add)
{
    if (!vertex)
    {
        return nullptr;
    }
    if (vertex->getValue() > to_add->getValue())
    {
        if (vertex->getLeft())
        {
            vertex->setLeft(insertAndBalance(vertex->getLeft(),to_add));
        }
        else
        {
            vertex->setLeft(to_add);
        }
    }
    else
    {
        if (vertex->getRight())
        {
            vertex->setRight(insertAndBalance(vertex->getRight(),to_add));
        }
        else
        {
            vertex->setRight(to_add);
        }
    }
    vertex->setHeight(getMaxInt(vertex->getRight()->getHeight(),vertex->getLeft()->getHeight())+1);
    return balance(vertex);
}

template<class T>
static Vertex<T> *getVertexByValue(Vertex<T> *vertex, const T &value)
{
    if (vertex)
    {
        if (vertex->getValue() == value)
        {
            return vertex;
        }
        else if (vertex->getValue() > value)
        {
            return getVertexByValue(vertex->getLeft(),value);
        }
        else
        {
            return getVertexByValue(vertex->getRight(),value);
        }
    }
    return nullptr;
}

template<class T>
void AvlTree<T>::insert(const T &value)
{
    if (getVertexByValue(root,value))
    {
        throw Failure();
    }
    Vertex<T>* new_vertex = new Vertex<T>(value);
    new_vertex->setHeight(0);
    if (!new_vertex)
    {
        return;
    }
    if (!root)
    {
        root = new_vertex;
        max = new_vertex;
    }
    else
    {
        root = insertAndBalance(root,new_vertex);
        if (max &&  (value > max->getValue()))
        {
            max = new_vertex;
        }
    }
    size++;
}

template<class T>
static Vertex<T>* removeAndBalance(Vertex<T> *vertex, const T &value)
{
    if (!vertex)
    {
        return nullptr;
    }
    if (vertex->getValue() > value)
    {
        vertex->setLeft(removeAndBalance(vertex->getLeft(),value));
    }
    else if (vertex->getValue() < value)
    {
        vertex->setRight(removeAndBalance(vertex->getRight(),value));
    }
    else
    {
        Vertex<T>* tmp;
        if (!vertex->getLeft() && !vertex->getRight())
        {
            tmp = vertex;
            vertex = nullptr;
            delete tmp;
        }
        else if (!vertex->getRight() || !vertex->getLeft())
        {
            tmp = vertex->getLeft() ? vertex->getLeft() : vertex->getRight();
            delete vertex;
            vertex = tmp;
        }
        else
        {
            tmp = vertex->getRight();
            while (tmp->getLeft())
            {
                tmp = tmp->getLeft();
            }
            T tmp_value = vertex->getValue();
            vertex->setValue(tmp->getValue());
            tmp->setValue(tmp_value);
            vertex->setRight(removeAndBalance(vertex->getRight(),tmp_value));
        }
    }
    if (!vertex)
    {
        return nullptr;
    }
    vertex->setHeight(getMaxInt(vertex->getLeft()->getHeight(),vertex->getRight()->getHeight())+1);
    return balance(vertex);
}

template<class T>
void AvlTree<T>::remove(const T &value)
{
    if (!getVertexByValue(root,value))
    {
        throw Failure();
    }
    root = removeAndBalance(root,value);
    Vertex<T>* tmp = root;
    while(tmp->getRight())
    {
        tmp = tmp->getRight();
    }
    max = tmp;
    size--;
}

template<class T>
void AvlTree<T>::changeField(int value, Vertex<T> *vertex, void (*func)(T &, int))
{
    if (!vertex)
    {
        return;
    }
    changeField(value,vertex->getLeft(),func);
    func(vertex->getValue(),value);
    changeField(value,vertex->getRight(),func);
}

template<class T>
static void inorderIteration(Vertex<T>* vertex, int number, T *array, int* index)
{
    if (vertex && *index < number)
    {
        inorderIteration(vertex->getLeft(),number,array,index);
        if (*index >= number)
        {
            return;
        }
        array[*index] = vertex->getValue();
        (*index)++;
        inorderIteration(vertex->getRight(),number,array,index);
    }
}

template<class T>
static T* mergeTwoArrays(const T* array1, const T* array2, int n1, int n2)
{
    T* merged = new T[n1+n2];
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2)
    {
        if (array1[i] < array2[j])
        {
            merged[k++] = array1[i++];
        }
        else
        {
            merged[k++] = array2[j++];
        }
    }
    while (i < n1)
    {
        merged[k++] = array1[i++];
    }
    while (j < n2)
    {
        merged[k++] = array2[j++];
    }
    return merged;
}

template<class T>
static Vertex<T>* sortedArrayToAvlTree(const T array[], int first, int last)
{
    if (first > last)
    {
        return nullptr;
    }
    int mid = (first + last)/2;
    Vertex<T>* vertex(new Vertex<T>(array[mid]));
    vertex->setLeft(sortedArrayToAvlTree(array,first,mid-1));
    vertex->setRight(sortedArrayToAvlTree(array,mid+1,last));
    vertex->setHeight(getMaxInt(vertex->getLeft()->getHeight(),vertex->getRight()->getHeight())+1);
    return vertex;
}

template<class T>
std::shared_ptr<AvlTree<T>> AvlTree<T>::mergeTrees(const AvlTree<T> &t1, const AvlTree<T> &t2)
{
    int n1 = t1.getSize(), i1 = 0;
    int n2 = t2.getSize(), i2 = 0;
    int n3 = n1 + n2;
    T* array1 = n1 > 0 ? new T[n1]() : nullptr;
    T* array2 = n2 > 0 ? new T[n2]() : nullptr;
    inorderIteration(t1.root,n1,array1,&i1);
    inorderIteration(t2.root,n2,array2,&i2);
    T* array3 = mergeTwoArrays(array1,array2,n1,n2);
    delete[] array1;
    delete[] array2;
    std::shared_ptr<AvlTree<T>> merged_tree = std::make_shared<AvlTree<T>>(AvlTree<T>());
    merged_tree->root = sortedArrayToAvlTree(array3,0,n3-1);
    delete[] array3;
    Vertex<T>* tmp = merged_tree->root;
    while (tmp->getRight())
    {
        tmp = tmp->getRight();
    }
    merged_tree->max = tmp;
    merged_tree->size = n3;
    return merged_tree;
}

template<class T>
T *AvlTree<T>::getPtrValue(const T &value)
{
    Vertex<T>* vertex = getVertexByValue(root,value);
    if (!vertex)
    {
        return nullptr;
    }
    return &vertex->getValue();
}

template<class T>
void AvlTree<T>::storeReverseInorder(Vertex<T>* vertex,int *array, int *index, int number,
                                     void (*func)(const T &, int *, int *))
{
    if (vertex && *index < number)
    {
        storeReverseInorder(vertex->getRight(),array,index,number,func);
        if (*index >= number)
        {
            return;
        }
        func(vertex->getValue(),array,index);
        storeReverseInorder(vertex->getLeft(),array,index,number,func);
    }
}

template<class T>
void AvlTree<T>::storeInorder(Vertex<T>* vertex,int *array, int *index, int number,
                              void (*func)(const T &, int *, int *))
{
    if (vertex && *index < number)
    {
        storeInorder(vertex->getLeft(),array,index,number,func);
        if (*index >= number)
        {
            return;
        }
        func(vertex->getValue(),array,index);
        storeInorder(vertex->getRight(),array,index,number,func);
    }
}

template<class T>
void AvlTree<T>::countWithinCondition(Vertex<T>* vertex,int *total_num, int *num,const T& min_val,const T& max_val,
                                      int a, int b, void (*func)(const T &, int, int, int *, int *))
{
    if (!vertex)
    {
        return;
    }
    if ((vertex->getValue() == max_val) && (vertex->getValue() == min_val))
    {
        func(vertex->getValue(),a,b,total_num,num);
        return;
    }
    if ((vertex->getValue() <= max_val) && (vertex->getValue() >= min_val))
    {
        func(vertex->getValue(),a,b,total_num,num);
        countWithinCondition(vertex->getLeft(),total_num,num,min_val,max_val,a,b,func);
        countWithinCondition(vertex->getRight(),total_num,num,min_val,max_val,a,b,func);
        return;
    }
    else if (vertex->getValue() < min_val)
    {
        countWithinCondition(vertex->getRight(),total_num,num,min_val,max_val,a,b,func);
        return;
    }
    else
    {
        countWithinCondition(vertex->getLeft(),total_num,num,min_val,max_val,a,b,func);
        return;
    }
}

#endif //AVLTREE_H_
