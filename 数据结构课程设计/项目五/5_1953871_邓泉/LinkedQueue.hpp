#pragma once
#include <iostream>
#include <assert.h>
using namespace std;



//�����
template <class T>
struct LinkNode
{
    //���캯��
    LinkNode(const T& value, LinkNode<T>* next = NULL) : data(value), link(next) {}
    LinkNode(LinkNode<T>* next = NULL) : link(next) {}

    T data;
    LinkNode<T>* link;
};


//������
template<class T>
class LinkedQueue
{
public:
    //���캯��
    LinkedQueue() :front(NULL), rear(NULL) {}

    //��������
    ~LinkedQueue() { makeEmpty(); }

    //�ÿն���
    void makeEmpty()
    {
        LinkNode<T>* del;					//���ɾ�������еĽ��
        while (front != NULL)
        {
            del = front;
            front = front->link;
            delete del;
        }
    }

    //�ж��Ƿ�Ϊ��
    bool isEmpty()
    {
        return front == NULL;
    }

    //���
    bool EnQueue(const T& x)
    {
        if (isEmpty())				//�ն���ʱ
        {
            front = rear = new LinkNode<T>(x);
            if (front == NULL)			//�����½��ʧ��
            {
                return false;
            }
        }
        else							//�ǿն���ʱ������β׷���µĽ�㲢���¶�βָ��
        {
            rear->link = new LinkNode<T>(x);
            if (rear->link == NULL)		//�����½��ʧ��
            {
                return false;
            }
            rear = rear->link;
        }
        return true;
    }

    //����
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
    LinkNode<T>* front;     //ͷָ��
    LinkNode<T>* rear;      //βָ��
};