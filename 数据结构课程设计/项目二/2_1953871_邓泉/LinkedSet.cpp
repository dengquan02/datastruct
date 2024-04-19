#include "LinkedSet.h"

//���캯��
LinkedSet::LinkedSet()
{
	last = first = new SetNode;							//���ٸ���ͷ�ڵ�
}


//��������
LinkedSet::~LinkedSet()
{
	makeEmpty();
	if (first != NULL) {
		delete first;
	}
}


//�ÿ�
void LinkedSet::makeEmpty()
{
	SetNode* del;
	while (first->link != NULL) {	//������Ϊ��ʱ��ɾȥ���г�ͷ���������н��
		del = first->link;
		first->link = del->link;
		delete del;
	}
	last = first;					//�޸ı�βָ��
}


//�������������У���巨��
void LinkedSet::inputRear(const int endTag)			//endTag���������н����ı�־
{
	makeEmpty();								//���ÿ�����
	SetNode* newNode;
	int val;
	cin >> val;
	while (val != endTag) {
		newNode = new SetNode(val);
		if (newNode == NULL) {
			cerr << "�洢�������" << endl;
			exit(1);
		}
		last = last->link = newNode;				//���뵽��ĩ��
		cin >> val;
	}
}


//��this��R�Ľ�����������ͨ��temp���أ����ı�this��R��
LinkedSet& LinkedSet::operator*(const LinkedSet& R)
{
	static LinkedSet temp;
	SetNode* pa = first->link;						//this����ɨ��ָ��
	SetNode* pb = R.first->link;					//R����ɨ��ָ��
	SetNode* pc = temp.first;						//������Ĵ��ָ��

	while (pa != NULL && pb != NULL) {
		if (pa->data == pb->data) {					//Ԫ����ͬ
			pc->link = new SetNode(pa->data);		//��������β��
			pa = pa->link;
			pb = pb->link;
			pc = pc->link;
		}
		else if (pa->data < pb->data) {				//a��Ԫ�ؽ�С
			pa = pa->link;
		}
		else {										//b��Ԫ�ؽ�С
			pb = pb->link;
		}
	}
	temp.last = pc;									//����βָ��
	return temp;
}


//����R��this
LinkedSet& LinkedSet::operator=(const LinkedSet& R)
{
	makeEmpty();									//���ÿ�this��
	SetNode* p = R.first->link;
	while (p != NULL) {
		last->link = new SetNode(p->data);
		last = last->link;
		p = p->link;
	}
	return *this;
}


//���
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




