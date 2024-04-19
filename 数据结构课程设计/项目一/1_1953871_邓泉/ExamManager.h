#pragma once
#include <iostream>
using namespace std;


//链表结点类（单个学生类）定义
struct LinkNode
{
	string m_code;			//考号
	string m_name;			//姓名
	string m_gender;		//性别
	string m_age;			//年龄
	string m_category;		//报考类别
	LinkNode* link;

	//构造函数
	LinkNode(string code = "", string name = "", string gender = "",
		string age = "", string category = "", LinkNode* ptr = NULL)
	{
		m_code = code;
		m_name = name;
		m_gender = gender;
		m_age = age;
		m_category = category;
		link = ptr;
	}
};


//单链表类定义
class List :public LinkNode
{
public:
	List();										//构造函数
	~List();									//析构函数
	void inputRear();							//建立考生信息（后插法）
	void makeEmpty();							//清空考生信息
	void output()const;							//统计考生信息
	void Insert();								//插入
	void Remove();								//删除
	void Find()const;							//查找
	void Change();								//修改
	bool isExist(string code)const;				//检测考号是否已存在

private:
	LinkNode* first;	//链表头指针
	LinkNode* last;		//链表尾指针
	int length;			//链表长度（考生人数）
};