#include "EWNet.h"



void EWNet::NEW(int sz) {
	for (int i = 0; i < sz; i++)
		for (int j = 0; j < sz; j++)
		{
			Edge[i][j] = maxsize;
			Lowcost[i][j] = maxsize;
		}
};


//寻找相应顶点
int EWNet::getvertice(char vs)
{
	for (int i = 0; i < numvs; i++)
	{
		if (vertice[i] == vs)
			return i;
	}

	return -1;
};


//输出顶点
void EWNet::OutputVertice()
{
	for (int i = 0; i < numvs; i++)
	{
		cout << vertice[i] << " ";
	}
}


//生成最小生成树
void EWNet::Prim(int start)
{
	if (temp == 0)
	{
		for (int i = 0; i < numvs; i++)
		{
			lowcost[i] = nearvex[i] = 1000;			//初始化最小消耗为无穷
		}
		nearvex[start] = -1;
		for (int i = 0; i < numvs; i++)
		{
			lowcost[i] = Edge[start][i];
		}
		temp++;
		Prim(start);								//第一个点进集合
	}
	if (temp != 0 && temp < numvs)
	{
		int low = 1000, sig = 0;
		for (int i = 0; i < numvs; i++)
		{
			if (nearvex[i] != -1)
			{
				if (lowcost[i] > Edge[i][start])
				{
					lowcost[i] = Edge[i][start];
					nearvex[i] = start;
				}
			}
		}
		//比较新点和原先的lowcost；做更新
		for (int i = 0; i < numvs; i++)
		{
			if (low >= lowcost[i] && nearvex[i] != -1)
			{
				low = lowcost[i];
				sig = i;
			}
		}
		cout << vertice[start] << "-" << "<" << low << ">" << "->" << vertice[sig] << "   ";//输出路径；
		nearvex[sig] = -1;
		Lowcost[sig][start] = Lowcost[start][sig] = lowcost[sig];
		temp++;
		Prim(sig);
	}

}


//输出边
void EWNet::OutputEdge()
{
	for (int i = 0; i < numvs; i++)
	{
		for (int j = 0; j < numvs; j++)
		{
			cout << Edge[i][j] << " ";
			if (j == numvs - 1)cout << "\n";
		}

	}
};


//输出最小花费
void EWNet::OutputLowcost()
{
	for (int i = 0; i < numvs; i++)
	{
		for (int j = 0; j < numvs; j++)
		{
			cout << Lowcost[i][j] << " ";
			if (j == numvs - 1)cout << "\n";
		}

	}
};


//向图中插入边
void EWNet::Insert(char v1, char v2, int value)
{
	int v1pos = getvertice(v1);

	int v2pos = getvertice(v2);

	Edge[v1pos][v2pos] = Edge[v2pos][v1pos] = value;
};