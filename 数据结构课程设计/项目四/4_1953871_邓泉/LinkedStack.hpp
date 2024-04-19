#pragma once
#include <iostream>
#include <assert.h>
using namespace std;


template <class T>
struct LinkNode
{
public:

    //构造函数
    LinkNode(const T& value, LinkNode<T>* next = NULL) : data(value), link(next) {}
    LinkNode(LinkNode<T>* next = NULL) : link(next) {}

    T data;
    LinkNode<T>* link;
};


template <class T>
class LinkedStack
{
public:

    //构造函数
    LinkedStack()
    {
        top = NULL;
    }

    //析构函数
    ~LinkedStack()
    {
        makeEmpty();
    }

    //清空栈的内容
    void makeEmpty()
    {
        LinkNode<T>* del;
        while (top != NULL)
        {
            del = top;
            top = top->link;
            delete del;
        }

    }

    //进栈
    void Push(const T& x)
    {
        top = new LinkNode<T>(x, top);
        assert(top != NULL);               //创建新结点失败退出
    }

    //退栈（删除栈顶结点，不需返回栈顶元素的值）
    bool Pop()
    {
        if (!isEmpty())
        {
            LinkNode<T>* p = top;
            top = top->link;
            delete p;
            return true;
        }
        return false;
    }

    //退栈（删除栈顶结点，并返回栈顶元素的值）
    bool Pop(T& x)
    {
        if (!isEmpty())
        {
            LinkNode<T>* p = top;
            top = top->link;
            x = p->data;
            delete p;
            return true;
        }
        return false;
    }

    //判栈空
    bool isEmpty()
    {
        return top == NULL;
    }

    //返回栈顶元素的值
    bool getTop(T& x)
    {
        if (isEmpty())
        {
            return false;
        }
        x = top->data;
        return true;
    }

private:
    LinkNode<T>* top;
};