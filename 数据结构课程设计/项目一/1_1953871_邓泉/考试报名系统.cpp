#include <iostream>
#include "ExamManager.h"

using namespace std;

int main()
{
	cout << "首先请建立考生信息系统！" << endl;
	List L;
	L.inputRear();
	L.output();
	cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;

	int choice;
	while (1) {
		cout << "\n请输入您要进行的操作：";
		cin >> choice;
		switch (choice) {
		case 1:L.Insert(); break;
		case 2:L.Remove(); break;
		case 3:L.Find(); break;
		case 4:L.Change(); break;
		case 5:L.output(); break;
		case 0:exit(0); break;
		default:cout << "抱歉，您想要进行的操作不存在，请重新输入！" << endl; break;
		}
	}
	system("pause");
	return 0;
}