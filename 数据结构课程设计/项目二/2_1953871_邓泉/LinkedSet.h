#pragma once
#include <iostream>
using namespace std;

//����ඨ��
struct SetNode
{
	int data;
	SetNode* link;

	//���캯��
	SetNode() :data(0), link(NULL) {};
	SetNode(const int& x, SetNode* ptr = NULL) :data(x), link(ptr) {};
};

//������������
class LinkedSet :public SetNode
{
public:
	LinkedSet();										//���캯��
	~LinkedSet();										//��������
	void makeEmpty();									//�ÿ�
	void inputRear(const int endTeg);					//�������������У���巨��
	LinkedSet& operator*(const LinkedSet& R);			//��this��R�Ľ���
	LinkedSet& operator=(const LinkedSet& R);			//����R��this
	void output()const;									//���
private:
	SetNode* first, * last;
};

