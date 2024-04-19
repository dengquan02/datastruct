#include<iostream>
#include<string>
#include"math.h"
#include<stdlib.h> 

using namespace std;


int main()
{
	int LeafNum = 0, temp = 0;
	cout << "��������Ҫ��ľͷ��ɼ��飿��";
	cin >> LeafNum;
	while (LeafNum <= 0)
	{
		cout << "���������������������";
		cin >> LeafNum;
	}

	int* a = (int*)calloc(LeafNum, sizeof(int));
	if (a == NULL)
	{
		cerr << "�ڴ�������";
		exit(1);
	}

	cout << "������ÿ��ľͷ�ĳ��ȣ�";
	for (int i = 0; i < LeafNum; i++)
	{
		cin >> a[i];
	}
	int* OringinalTree = (int*)calloc(LeafNum, sizeof(int));//����������
	int* HuffmanTree = (int*)calloc(LeafNum, sizeof(int));//�ź�������������


	for (int i = 0; i < LeafNum; i++)
	{
		OringinalTree[i] = a[i];
	}
	for (int i = 0; i < LeafNum - 1; i++)
	{
		long long int min1 = 1000000, min2 = 1000000;
		for (int j = 0; j < LeafNum; j++)
		{
			if (min1 >= OringinalTree[j] && OringinalTree[j] > 0)
			{
				temp = j;
				min1 = OringinalTree[j];
			}
		}
		OringinalTree[temp] = 0;
		for (int j = 0; j < LeafNum; j++)
		{
			if (min2 >= OringinalTree[j] && OringinalTree[j] > 0)
			{
				temp = j;
				min2 = OringinalTree[j];
			}
		}
		HuffmanTree[i] = OringinalTree[temp] = min1 + min2;
		min1 = min2 = 100000;
	}

	int sum = 0;
	for (int i = 0; i < LeafNum; i++) {
		sum += HuffmanTree[i];
	}
	cout << "��С����Ϊ��" << sum << endl;

	system("pause");
	return 0;
}