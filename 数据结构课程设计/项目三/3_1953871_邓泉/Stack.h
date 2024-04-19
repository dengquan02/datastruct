#pragma once
#include <iostream>
using namespace std;



template <class T>
struct LinkNode
{
public:

    //构造函数
    LinkNode(const T& value = -1, LinkNode<T>* next = NULL) : data(value), link(next) {}
    LinkNode(LinkNode<T>* next = NULL) : link(next) {}

    T data;
    LinkNode<T>* link;
};

template <class T>
class Stack
{
public:

    //构造函数
    Stack()
    {
        elements = NULL;
        top = 0;
    }

    //析构函数
    ~Stack()
    {
        delete[]elements;
    }

    void Push(T t)
    {
        LinkNode<T>* oldFirst = elements;
        elements = new LinkNode<T>(t, oldFirst);
        ++top;
    }

    void Pop()
    {
        if (isEmpty())
            return;
        LinkNode<T>* temp = elements;
        elements = elements->link;
        delete temp;
        --top;
    }


    bool isEmpty()
    {
        return top == 0;
    }

    T getTop()
    {
        return elements->data;
    }

private:
    LinkNode<T>* elements = NULL;
    int top = 0;
};