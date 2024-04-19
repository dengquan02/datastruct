#include "LinkedSet.h"

//构造函数
LinkedSet::LinkedSet()
{
	last = first = new SetNode;							//开辟附加头节点
}


//析构函数
LinkedSet::~LinkedSet()
{
	makeEmpty();
	if (first != NULL) {
		delete first;
	}
}


//置空
void LinkedSet::makeEmpty()
{
	SetNode* del;
	while (first->link != NULL) {	//当链不为空时，删去链中除头结点外的所有结点
		del = first->link;
		first->link = del->link;
		delete del;
	}
	last = first;					//修改表尾指针
}


//建立单链表序列（后插法）
void LinkedSet::inputRear(const int endTag)			//endTag是输入序列结束的标志
{
	makeEmpty();								//先置空序列
	SetNode* newNode;
	int val;
	cin >> val;
	while (val != endTag) {
		newNode = new SetNode(val);
		if (newNode == NULL) {
			cerr << "存储分配错误！" << endl;
			exit(1);
		}
		last = last->link = newNode;				//插入到表末端
		cin >> val;
	}
}


//求this与R的交集（计算结果通过temp返回，不改变this和R）
LinkedSet& LinkedSet::operator*(const LinkedSet& R)
{
	static LinkedSet temp;
	SetNode* pa = first->link;						//this的链扫描指针
	SetNode* pb = R.first->link;					//R的链扫描指针
	SetNode* pc = temp.first;						//结果链的存放指针

	while (pa != NULL && pb != NULL) {
		if (pa->data == pb->data) {					//元素相同
			pc->link = new SetNode(pa->data);		//插入结果链尾部
			pa = pa->link;
			pb = pb->link;
			pc = pc->link;
		}
		else if (pa->data < pb->data) {				//a链元素较小
			pa = pa->link;
		}
		else {										//b链元素较小
			pb = pb->link;
		}
	}
	temp.last = pc;									//置链尾指针
	return temp;
}


//复制R到this
LinkedSet& LinkedSet::operator=(const LinkedSet& R)
{
	makeEmpty();									//先置空this链
	SetNode* p = R.first->link;
	while (p != NULL) {
		last->link = new SetNode(p->data);
		last = last->link;
		p = p->link;
	}
	return *this;
}


//输出
void LinkedSet::output()const
{
	if (first == last) {
		cout << "NULL" << endl;
	}
	else {
		SetNode* current = first->link;
		while (current != NULL) {
			cout << current->data << " ";
			current = current->link;
		}
		cout << endl;
	}
}




