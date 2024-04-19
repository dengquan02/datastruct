#pragma once
#include <iostream>
using namespace std;

const int maxsize = 1000;



class EWNet
{
public:
	
	void NEW(int sz);
	
	int getvertice(char vs);						//Ѱ����Ӧ����

	void OutputVertice();							//�������

	void OutputLowcost();							//�����С����

	void OutputEdge();								//�����

	void Insert(char v1, char v2, int value);		//��ͼ�в����

	void Prim(int start);							//Prim�㷨������С������


	int numvs = 0;
	char* vertice = NULL;
	int** Edge = NULL, ** Lowcost = NULL;
	int temp = 0;
	int* lowcost = NULL;
	int* nearvex = NULL;
};