#include <iostream>
#include "ExamManager.h"

using namespace std;

int main()
{
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	List L;
	L.inputRear();
	L.output();
	cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;

	int choice;
	while (1) {
		cout << "\n��������Ҫ���еĲ�����";
		cin >> choice;
		switch (choice) {
		case 1:L.Insert(); break;
		case 2:L.Remove(); break;
		case 3:L.Find(); break;
		case 4:L.Change(); break;
		case 5:L.output(); break;
		case 0:exit(0); break;
		default:cout << "��Ǹ������Ҫ���еĲ��������ڣ����������룡" << endl; break;
		}
	}
	system("pause");
	return 0;
}