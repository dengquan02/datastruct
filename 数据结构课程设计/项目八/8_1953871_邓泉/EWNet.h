#pragma once
#include <iostream>
using namespace std;

const int maxsize = 1000;



class EWNet
{
public:
	
	void NEW(int sz);
	
	int getvertice(char vs);						//寻找相应顶点

	void OutputVertice();							//输出顶点

	void OutputLowcost();							//输出最小花费

	void OutputEdge();								//输出边

	void Insert(char v1, char v2, int value);		//向图中插入边

	void Prim(int start);							//Prim算法生成最小生成树


	int numvs = 0;
	char* vertice = NULL;
	int** Edge = NULL, ** Lowcost = NULL;
	int temp = 0;
	int* lowcost = NULL;
	int* nearvex = NULL;
};