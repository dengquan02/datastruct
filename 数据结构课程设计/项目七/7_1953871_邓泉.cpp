#include<iostream>
#include<string>
#include"math.h"
#include<stdlib.h> 

using namespace std;


int main()
{
	int LeafNum = 0, temp = 0;
	cout << "请问您想要将木头锯成几块？：";
	cin >> LeafNum;
	while (LeafNum <= 0)
	{
		cout << "输入错误！请输入正整数：";
		cin >> LeafNum;
	}

	int* a = (int*)calloc(LeafNum, sizeof(int));
	if (a == NULL)
	{
		cerr << "内存分配错误！";
		exit(1);
	}

	cout << "请输入每块木头的长度：";
	for (int i = 0; i < LeafNum; i++)
	{
		cin >> a[i];
	}
	int* OringinalTree = (int*)calloc(LeafNum, sizeof(int));//操作的数组
	int* HuffmanTree = (int*)calloc(LeafNum, sizeof(int));//放后来产生的数的


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
	cout << "最小花费为：" << sum << endl;

	system("pause");
	return 0;
}