#pragma once
#include <iostream>
#include <assert.h>
using namespace std;


template <class T>
struct LinkNode
{
public:

    //���캯��
    LinkNode(const T& value, LinkNode<T>* next = NULL) : data(value), link(next) {}
    LinkNode(LinkNode<T>* next = NULL) : link(next) {}

    T data;
    LinkNode<T>* link;
};


template <class T>
class LinkedStack
{
public:

    //���캯��
    LinkedStack()
    {
        top = NULL;
    }

    //��������
    ~LinkedStack()
    {
        makeEmpty();
    }

    //���ջ������
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

    //��ջ
    void Push(const T& x)
    {
        top = new LinkNode<T>(x, top);
        assert(top != NULL);               //�����½��ʧ���˳�
    }

    //��ջ��ɾ��ջ����㣬���践��ջ��Ԫ�ص�ֵ��
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

    //��ջ��ɾ��ջ����㣬������ջ��Ԫ�ص�ֵ��
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

    //��ջ��
    bool isEmpty()
    {
        return top == NULL;
    }

    //����ջ��Ԫ�ص�ֵ
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