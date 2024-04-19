#include <iostream>
#include "EWNet.h"
using namespace std;



char op;
int Vnum, Evalue;
int produce = 0;
char vname, vname1, vname2, vstart;


int main()
{
	cout << "**            电网造价模拟系统           **\n"
		 << "===========================================\n"
   		 << "**           A --- 创建电网顶点          **\n"
 		 << "**           B --- 添加电网的边          **\n"
		 << "**           C --- 构造最小生成树        **\n"
		 << "**           D --- 显示最小生成树        **\n"
		 << "**           E --- 退出程序              **\n"
		 << "===========================================\n";


	EWNet* electric = new EWNet;
	while (true)
	{
		cout << "\n请选择操作：";
		cin >> op;
		switch (op)
		{

		case'A':
		{
			cout << "请输入顶点的个数：";
			cin >> Vnum;

			electric->numvs = Vnum;
			electric->vertice = (char*)calloc(Vnum, sizeof(char));
			electric->Edge = (int**)malloc(sizeof(int) * Vnum);
			for (int i = 0; i < Vnum; i++)
			{
				electric->Edge[i] = new int;		//动态分配内存
			}

			electric->Lowcost = (int**)malloc(sizeof(int) * Vnum);
			if (electric->Lowcost == NULL)
			{
				cerr << "内存分配错误！";
				exit(1);
			}
			for (int i = 0; i < Vnum; i++)
			{			
				electric->Lowcost[i] = (int*)malloc(sizeof(int) * Vnum);
			}

			electric->NEW(Vnum);
			cout << "请依次输入各点的名称：" << endl;
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
				cout << "请输入两个顶点及边：";
				cin >> vname1 >> vname2 >> Evalue;
				electric->Insert(vname1, vname2, Evalue);//向图中插入边
			}
			cout << endl;
		}
		break;

		case'C':
		{
			produce = 1;
			cout << "请输入起始顶点：";
			cin >> vstart;
			cout << "生成Prim最小生成树！" << endl;
		}
		break;

		case'D':
		{
			if (produce == 1)
			{
				cout << "最小生成树的顶点及边为：\n";
				int start = electric->getvertice(vstart);
				electric->lowcost = (int*)malloc(sizeof(int) * Vnum);
				electric->nearvex = (int*)malloc(sizeof(int) * Vnum);
				electric->Prim(start);
				cout << endl;
			}
			else
			{
				cout << "请先生成！";
			}
		}
		break;

		case'E':
		{return 0; }
		break;

		default:cerr << "错误！！！！";
			break;
		}
	}

	system("pause");
	return 0;
}