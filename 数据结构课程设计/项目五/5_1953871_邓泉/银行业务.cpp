#include<iostream>
#include "LinkedQueue.hpp"
using namespace std;

//全局变量
LinkedQueue<int> A, B;

//输入
void Input()
{
	cout << "请输入顾客总数：";
	int N;
	cin >> N;
	while (N <= 0)
	{
		cerr << "总数输入错误！请重新输入：";
		cin >> N;
	}

	cout << "请输入N位顾客的编号：";
	int customer;
	int cnt = 0;
	while (true)
	{
		while (N--)
		{
			cin >> customer;
			if (customer <= 0)
			{
				cnt++;
			}
			else if (customer % 2 == 1)				//如果是奇数
			{
				A.EnQueue(customer);
			}
			else									//如果是偶数
			{
				B.EnQueue(customer);
			}
		}

		if (cnt > 0)
		{
			cout << "有" << cnt << "位顾客编号输入有误！请补充输入：";
			N = cnt;
		}
		else
		{
			break;
		}
	}
}


//输出
void Output()
{
	//输出（A出两个，B出一个）
	cout << "处理完成的顺序为：";
	int customer;
	while (!A.isEmpty() || !B.isEmpty())
	{
		for (int i = 0; !A.isEmpty() && i < 2; i++)
		{
			A.DeQueue(customer);
			cout << customer << " ";
		}

		if (!B.isEmpty())
		{
			B.DeQueue(customer);
			cout << customer << " ";
		}
	}
	cout << endl;
}


int main()
{
	Input();
	Output();

	system("pause");
	return 0;
}