#pragma once
#include <iostream>
using namespace std;

//结点类定义
struct SetNode
{
	int data;
	SetNode* link;

	//构造函数
	SetNode() :data(0), link(NULL) {};
	SetNode(const int& x, SetNode* ptr = NULL) :data(x), link(ptr) {};
};

//有序链表序列
class LinkedSet :public SetNode
{
public:
	LinkedSet();										//构造函数
	~LinkedSet();										//析构函数
	void makeEmpty();									//置空
	void inputRear(const int endTeg);					//建立单链表序列（后插法）
	LinkedSet& operator*(const LinkedSet& R);			//求this与R的交集
	LinkedSet& operator=(const LinkedSet& R);			//复制R到this
	void output()const;									//输出
private:
	SetNode* first, * last;
};

