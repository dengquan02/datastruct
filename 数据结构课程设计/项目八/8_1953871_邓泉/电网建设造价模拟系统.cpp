#include <iostream>
#include "EWNet.h"
using namespace std;



char op;
int Vnum, Evalue;
int produce = 0;
char vname, vname1, vname2, vstart;


int main()
{
	cout << "**            �������ģ��ϵͳ           **\n"
		 << "===========================================\n"
   		 << "**           A --- ������������          **\n"
 		 << "**           B --- ��ӵ����ı�          **\n"
		 << "**           C --- ������С������        **\n"
		 << "**           D --- ��ʾ��С������        **\n"
		 << "**           E --- �˳�����              **\n"
		 << "===========================================\n";


	EWNet* electric = new EWNet;
	while (true)
	{
		cout << "\n��ѡ�������";
		cin >> op;
		switch (op)
		{

		case'A':
		{
			cout << "�����붥��ĸ�����";
			cin >> Vnum;

			electric->numvs = Vnum;
			electric->vertice = (char*)calloc(Vnum, sizeof(char));
			electric->Edge = (int**)malloc(sizeof(int) * Vnum);
			for (int i = 0; i < Vnum; i++)
			{
				electric->Edge[i] = new int;		//��̬�����ڴ�
			}

			electric->Lowcost = (int**)malloc(sizeof(int) * Vnum);
			if (electric->Lowcost == NULL)
			{
				cerr << "�ڴ�������";
				exit(1);
			}
			for (int i = 0; i < Vnum; i++)
			{			
				electric->Lowcost[i] = (int*)malloc(sizeof(int) * Vnum);
			}

			electric->NEW(Vnum);
			cout << "�����������������ƣ�" << endl;
			for (int i = 0; i < Vnum; i++)
			{
				cin >> vname;
				electric->vertice[i] = vname;
			}
			cout << endl;
		}
		break;

		case'B':
		{
			for (int i = 0; i < Vnum * (Vnum - 1) / 2; i++)
			{
				cout << "�������������㼰�ߣ�";
				cin >> vname1 >> vname2 >> Evalue;
				electric->Insert(vname1, vname2, Evalue);//��ͼ�в����
			}
			cout << endl;
		}
		break;

		case'C':
		{
			produce = 1;
			cout << "��������ʼ���㣺";
			cin >> vstart;
			cout << "����Prim��С��������" << endl;
		}
		break;

		case'D':
		{
			if (produce == 1)
			{
				cout << "��С�������Ķ��㼰��Ϊ��\n";
				int start = electric->getvertice(vstart);
				electric->lowcost = (int*)malloc(sizeof(int) * Vnum);
				electric->nearvex = (int*)malloc(sizeof(int) * Vnum);
				electric->Prim(start);
				cout << endl;
			}
			else
			{
				cout << "�������ɣ�";
			}
		}
		break;

		case'E':
		{return 0; }
		break;

		default:cerr << "���󣡣�����";
			break;
		}
	}

	system("pause");
	return 0;
}