#include "ExamManager.h"


//���캯��
List::List()
{
	last = first = new LinkNode;	//���ٸ���ͷ�ڵ�
	length = 0;
}


//��������
List::~List()
{
	makeEmpty();
	if (first != NULL) {
		delete first;
	}
}


//����������Ϣ����巨��
void List::inputRear()
{
	makeEmpty();					//����տ�����Ϣ
	cout << "�����뿼��������";
	int num;
	cin >> num;
	while (num < 0) {
		cout << "������һ���Ǹ�����:";
		cin >> num;
	}
	cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
	while (1) {
		int cnt = 0;								//ͳ�Ʋ���ʧ�ܵĴ���
		while (num--) {
			LinkNode* newNode = new LinkNode;
			if (newNode == NULL) {
				cerr << "�洢�������" << endl;
				exit(1);
			}
			cin >> newNode->m_code >> newNode->m_name >> newNode->m_gender >> newNode->m_age >> newNode->m_category;
			if (isExist(newNode->m_code)) {			//������ͬ�Ŀ���
				cnt++;
			}
			else {									//���ź���
				last = last->link = newNode;		//���뵽��β
				length++;							//����������
			}
		}
		if (cnt > 0) {
			cout << "��" << cnt << "λ��������ʧ�ܣ��벹�俼����Ϣ��" << endl;
			num = cnt;																				//���»������ѧ��������
		}
		else {																						//�ɹ������Ϣϵͳ����
			break;
		}
	}
}


//��տ�����Ϣ
void List::makeEmpty()
{
	LinkNode* del;
	while (first->link != NULL) {	//������Ϊ��ʱ��ɾȥ���г�ͷ���������н��
		del = first->link;
		first->link = del->link;
		delete del;
	}
	last = first;					//�޸ı�βָ��
	length = 0;						//����������
}


//ͳ�ƿ�����Ϣ
void List::output()const
{
	if (length == 0) {																//��������Ϊ��ʱ��������ϢΪ��
		cout << "��ǰ������ϢΪ�գ�" << endl;
		return;
	}

	cout << "\n����	����	�Ա�	����	�������" << endl;
	LinkNode* current = first->link;
	while (current != NULL) {
		cout << current->m_code << "	" << current->m_name << "	" << current->m_gender
			<< "	" << current->m_age << "	" << current->m_category << endl;
		current = current->link;													//�ƶ�����һ�����
	}
}


//����
void List::Insert()
{
	LinkNode* newNode = new LinkNode;
	if (newNode == NULL) {
		cerr << "�洢����ʧ�ܣ�" << endl;
		exit(1);
	}
	cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������" << endl;
	cin >> newNode->m_code >> newNode->m_name >> newNode->m_gender >> newNode->m_age >> newNode->m_category;

	if (isExist(newNode->m_code)) {															//���ڿ�����ͬ�����
		cout << "Ҫ����ѧ���Ŀ�����ԭϵͳ���Ѵ��ڣ�����ʧ�ܣ�" << endl;
	}
	else {
		last = last->link = newNode;														//��β�������µĽ��
		length++;																			//����������
		output();																			//ͳ���µĿ�����Ϣ
	}

}


//ɾ��
void List::Remove()
{
	cout << "������Ҫɾ���Ŀ����Ŀ��ţ�";
	string code;
	cin >> code;
	LinkNode* prior = first;															//Ҫɾ������ǰһ�����
	LinkNode* del = prior->link;														//Ҫɾ���Ľ��
	while (del != NULL) {
		if (del->m_code == code) {
			break;
		}
		prior = del;																	//����prior,del
		del = del->link;
	}
	if (del == NULL) {																	//ɾ��ʧ��
		cout << "ϵͳ�����޴˿�����Ϣ���޷�ɾ����" << endl;
		return;
	}
	cout << "��ɾ���Ŀ�����Ϣ�ǣ�" << del->m_code << "	" << del->m_name << "	"		//��ʾ��ɾ����������Ϣ
		<< del->m_gender << "	" << del->m_age << "	" << del->m_category << endl;
	prior->link = del->link;															//��������������ɾ��������ժ��
	delete del;																			//ɾ�����
	length--;																			//����������
	output();																			//ͳ���µĿ�����Ϣ
}


//����
void List::Find()const
{
	cout << "������Ҫ���ҵĿ����Ŀ��ţ�";
	string code;
	cin >> code;
	LinkNode* current = first->link;
	while (current != NULL) {																//ѭ������������code�Ľ��
		if (current->m_code == code) {
			cout << "����	����	�Ա�	����	�������" << endl;						//��ʾ�����ҵĿ�����Ϣ
			cout << current->m_code << "	" << current->m_name << "	" << current->m_gender
				<< "	" << current->m_age << "	" << current->m_category << endl;
			break;
		}
		current = current->link;															//currentָ����һ�����
	}
	if (current == NULL) {																	//����ʧ��
		cout << "ϵͳ�����޴˿�����Ϣ��" << endl;
	}
}


//�޸�
void List::Change()
{
	cout << "������Ҫ�޸ĵĿ����Ŀ��ţ�";
	string code;
	cin >> code;
	LinkNode* current = first->link;
	while (current != NULL && current->m_code != code) {								//ѭ������������code�Ľ��
		current = current->link;														//currentָ����һ�����
	}
	if (current == NULL) {																//����ʧ��
		cout << "ϵͳ�����޴˿�����Ϣ��" << endl;
	}
	else {
		string code; string name; string gender; string age; string category;
		cout << "����������˿����޸ĺ�Ŀ��ţ��������Ա����估�������" << endl;
		cin >> code >> name >> gender >> age >> category;
		if (code != current->m_code && isExist(code)) {						//�޸�ʧ��
			cout << "���ű��޸ĺ����������������ظ�,�޸�ʧ�ܣ�" << endl;
		}
		else {
			current->m_code = code;
			current->m_name = name;
			current->m_gender = gender;
			current->m_age = age;
			current->m_category = category;
			output();																	//��ʾ�µĿ�����Ϣ
		}
	}
}


//��⿼���Ƿ��Ѵ���
bool List::isExist(string code)const
{
	LinkNode* current = first->link;
	for (; current != NULL; current = current->link) {
		if (current->m_code == code) {
			break;
		}
	}
	if (current != NULL) {
		return true;									//�Ѵ��ڷ���true��
	}
	return false;										//���򷵻�false
}