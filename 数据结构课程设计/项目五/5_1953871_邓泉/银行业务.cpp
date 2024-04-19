#include<iostream>
#include "LinkedQueue.hpp"
using namespace std;

//ȫ�ֱ���
LinkedQueue<int> A, B;

//����
void Input()
{
	cout << "������˿�������";
	int N;
	cin >> N;
	while (N <= 0)
	{
		cerr << "��������������������룺";
		cin >> N;
	}

	cout << "������Nλ�˿͵ı�ţ�";
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
			else if (customer % 2 == 1)				//���������
			{
				A.EnQueue(customer);
			}
			else									//�����ż��
			{
				B.EnQueue(customer);
			}
		}

		if (cnt > 0)
		{
			cout << "��" << cnt << "λ�˿ͱ�����������벹�����룺";
			N = cnt;
		}
		else
		{
			break;
		}
	}
}


//���
void Output()
{
	//�����A��������B��һ����
	cout << "������ɵ�˳��Ϊ��";
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