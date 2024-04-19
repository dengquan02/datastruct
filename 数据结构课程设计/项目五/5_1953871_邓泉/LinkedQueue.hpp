#pragma once
#include <iostream>
#include <assert.h>
using namespace std;



//结点类
template <class T>
struct LinkNode
{
    //构造函数
    LinkNode(const T& value, LinkNode<T>* next = NULL) : data(value), link(next) {}
    LinkNode(LinkNode<T>* next = NULL) : link(next) {}

    T data;
    LinkNode<T>* link;
};


//队列类
template<class T>
class LinkedQueue
{
public:
    //构造函数
    LinkedQueue() :front(NULL), rear(NULL) {}

    //析构函数
    ~LinkedQueue() { makeEmpty(); }

    //置空队列
    void makeEmpty()
    {
        LinkNode<T>* del;					//逐个删除队列中的结点
        while (front != NULL)
        {
            del = front;
            front = front->link;
            delete del;
        }
    }

    //判断是否为空
    bool isEmpty()
    {
        return front == NULL;
    }

    //入队
    bool EnQueue(const T& x)
    {
        if (isEmpty())				//空队列时
        {
            front = rear = new LinkNode<T>(x);
            if (front == NULL)			//分配新结点失败
            {
                return false;
            }
        }
        else							//非空队列时，在链尾追加新的结点并更新队尾指针
        {
            rear->link = new LinkNode<T>(x);
            if (rear->link == NULL)		//分配新结点失败
            {
                return false;
            }
            rear = rear->link;
        }
        return true;
    }

    //出队
    bool DeQueue(T& x)
    {
        if (isEmpty())
        {
            return false;
        }
        LinkNode<T>* p = front;
        x = p->data;
        front = front->link;
        delete p;
        return true;
    }


protected:
    LinkNode<T>* front;     //头指针
    LinkNode<T>* rear;      //尾指针
};