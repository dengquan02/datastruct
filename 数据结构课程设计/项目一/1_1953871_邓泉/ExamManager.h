#pragma once
#include <iostream>
using namespace std;


//�������ࣨ����ѧ���ࣩ����
struct LinkNode
{
	string m_code;			//����
	string m_name;			//����
	string m_gender;		//�Ա�
	string m_age;			//����
	string m_category;		//�������
	LinkNode* link;

	//���캯��
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


//�������ඨ��
class List :public LinkNode
{
public:
	List();										//���캯��
	~List();									//��������
	void inputRear();							//����������Ϣ����巨��
	void makeEmpty();							//��տ�����Ϣ
	void output()const;							//ͳ�ƿ�����Ϣ
	void Insert();								//����
	void Remove();								//ɾ��
	void Find()const;							//����
	void Change();								//�޸�
	bool isExist(string code)const;				//��⿼���Ƿ��Ѵ���

private:
	LinkNode* first;	//����ͷָ��
	LinkNode* last;		//����βָ��
	int length;			//�����ȣ�����������
};