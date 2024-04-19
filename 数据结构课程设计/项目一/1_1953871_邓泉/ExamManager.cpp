#include "ExamManager.h"


//构造函数
List::List()
{
	last = first = new LinkNode;	//开辟附加头节点
	length = 0;
}


//析构函数
List::~List()
{
	makeEmpty();
	if (first != NULL) {
		delete first;
	}
}


//建立考生信息（后插法）
void List::inputRear()
{
	makeEmpty();					//先清空考生信息
	cout << "请输入考生人数：";
	int num;
	cin >> num;
	while (num < 0) {
		cout << "请输入一个非负整数:";
		cin >> num;
	}
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
	while (1) {
		int cnt = 0;								//统计插入失败的次数
		while (num--) {
			LinkNode* newNode = new LinkNode;
			if (newNode == NULL) {
				cerr << "存储分配错误！" << endl;
				exit(1);
			}
			cin >> newNode->m_code >> newNode->m_name >> newNode->m_gender >> newNode->m_age >> newNode->m_category;
			if (isExist(newNode->m_code)) {			//存在相同的考号
				cnt++;
			}
			else {									//考号合理
				last = last->link = newNode;		//插入到表尾
				length++;							//更新链表长度
			}
		}
		if (cnt > 0) {
			cout << "有" << cnt << "位考生插入失败，请补充考生信息：" << endl;
			num = cnt;																				//更新还需插入学生的人数
		}
		else {																						//成功完成信息系统建立
			break;
		}
	}
}


//清空考生信息
void List::makeEmpty()
{
	LinkNode* del;
	while (first->link != NULL) {	//当链不为空时，删去链中除头结点外的所有结点
		del = first->link;
		first->link = del->link;
		delete del;
	}
	last = first;					//修改表尾指针
	length = 0;						//更新链表长度
}


//统计考生信息
void List::output()const
{
	if (length == 0) {																//当链表长度为零时，考生信息为空
		cout << "当前考生信息为空！" << endl;
		return;
	}

	cout << "\n考号	姓名	性别	年龄	报考类别" << endl;
	LinkNode* current = first->link;
	while (current != NULL) {
		cout << current->m_code << "	" << current->m_name << "	" << current->m_gender
			<< "	" << current->m_age << "	" << current->m_category << endl;
		current = current->link;													//移动到下一个结点
	}
}


//插入
void List::Insert()
{
	LinkNode* newNode = new LinkNode;
	if (newNode == NULL) {
		cerr << "存储分配失败！" << endl;
		exit(1);
	}
	cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;
	cin >> newNode->m_code >> newNode->m_name >> newNode->m_gender >> newNode->m_age >> newNode->m_category;

	if (isExist(newNode->m_code)) {															//存在考号相同的情况
		cout << "要插入学生的考号在原系统中已存在，插入失败！" << endl;
	}
	else {
		last = last->link = newNode;														//在尾部插入新的结点
		length++;																			//更新链表长度
		output();																			//统计新的考生信息
	}

}


//删除
void List::Remove()
{
	cout << "请输入要删除的考生的考号：";
	string code;
	cin >> code;
	LinkNode* prior = first;															//要删除结点的前一个结点
	LinkNode* del = prior->link;														//要删除的结点
	while (del != NULL) {
		if (del->m_code == code) {
			break;
		}
		prior = del;																	//更新prior,del
		del = del->link;
	}
	if (del == NULL) {																	//删除失败
		cout << "系统中暂无此考生信息，无法删除！" << endl;
		return;
	}
	cout << "你删除的考生信息是：" << del->m_code << "	" << del->m_name << "	"		//显示被删除考生的信息
		<< del->m_gender << "	" << del->m_age << "	" << del->m_category << endl;
	prior->link = del->link;															//重新拉链，将被删结点从链中摘下
	delete del;																			//删除结点
	length--;																			//更新链表长度
	output();																			//统计新的考生信息
}


//查找
void List::Find()const
{
	cout << "请输入要查找的考生的考号：";
	string code;
	cin >> code;
	LinkNode* current = first->link;
	while (current != NULL) {																//循链搜索含考号code的结点
		if (current->m_code == code) {
			cout << "考号	姓名	性别	年龄	报考类别" << endl;						//显示所查找的考生信息
			cout << current->m_code << "	" << current->m_name << "	" << current->m_gender
				<< "	" << current->m_age << "	" << current->m_category << endl;
			break;
		}
		current = current->link;															//current指向下一个结点
	}
	if (current == NULL) {																	//搜索失败
		cout << "系统中暂无此考生信息！" << endl;
	}
}


//修改
void List::Change()
{
	cout << "请输入要修改的考生的考号：";
	string code;
	cin >> code;
	LinkNode* current = first->link;
	while (current != NULL && current->m_code != code) {								//循链搜索含考号code的结点
		current = current->link;														//current指向下一个结点
	}
	if (current == NULL) {																//搜索失败
		cout << "系统中暂无此考生信息！" << endl;
	}
	else {
		string code; string name; string gender; string age; string category;
		cout << "请依次输入此考生修改后的考号，姓名，性别，年龄及报考类别！" << endl;
		cin >> code >> name >> gender >> age >> category;
		if (code != current->m_code && isExist(code)) {						//修改失败
			cout << "考号被修改后与其他考生考号重复,修改失败！" << endl;
		}
		else {
			current->m_code = code;
			current->m_name = name;
			current->m_gender = gender;
			current->m_age = age;
			current->m_category = category;
			output();																	//显示新的考生信息
		}
	}
}


//检测考号是否已存在
bool List::isExist(string code)const
{
	LinkNode* current = first->link;
	for (; current != NULL; current = current->link) {
		if (current->m_code == code) {
			break;
		}
	}
	if (current != NULL) {
		return true;									//已存在返回true，
	}
	return false;										//否则返回false
}