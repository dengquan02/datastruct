#include<iostream>
#include <vector>
#include "Stack.h"

using namespace std;

void DFS(vector<vector<int>>& map, vector<vector<bool>>& visited, 
    Stack<pair<int, int>>& path, int i, int j, int x1, int y1, bool& hasPath)
{
    int M = map.size(), N = map[0].size();
    path.Push(make_pair(i, j));
    visited[i][j] = true;
    if (i == x1 && j == y1)
    {
        hasPath = true;
        Stack<pair<int, int>> reverse;
        while (!path.isEmpty())
        {
            pair<int, int> p = path.getTop();
            path.Pop();
            reverse.Push(p);                                //将栈反转用于输出路径
            map[p.first][p.second] = 2;
        }

        cout << endl;
        cout << "      ";
        for (int i = 0; i < N; ++i)
        {
            cout << i << "列  ";
        }
        cout << endl;
        for (int i = 0; i < M; ++i)
        {
            cout << i << "行    ";
            for (int j = 0; j < N; ++j)
            {
                if (map[i][j] == 0)
                {
                    cout << "0";
                }
                else if (map[i][j] == 2)
                {
                    cout << "X";            //X代表路径
                }
                else
                {
                    cout << "#";
                }
                cout << "    ";
            }
            cout << endl;
        }

        cout << endl << "迷宫路径为:" << endl;
        while (!reverse.isEmpty())
        {
            pair<int, int> p = reverse.getTop();
            reverse.Pop();
            if (p.first == x1 && p.second == y1)
                cout << "(" << p.first << "," << p.second << ")" << endl;
            else
                cout << "(" << p.first << "," << p.second << ")->";
        }
    }
    if (i - 1 >= 0 && map[i - 1][j] == 0 && !visited[i - 1][j])
    {
        DFS(map, visited, path, i - 1, j, x1, y1, hasPath);
    }
    if (i + 1 < M && map[i + 1][j] == 0 && !visited[i + 1][j])
    {
        DFS(map, visited, path, i + 1, j, x1, y1, hasPath);
    }
    if (j + 1 < N && map[i][j + 1] == 0 && !visited[i][j + 1])
    {
        DFS(map, visited, path, i, j + 1, x1, y1, hasPath);
    }
    if (j - 1 >= 0 && map[i][j - 1] == 0 && !visited[i][j - 1])
    {
        DFS(map, visited, path, i, j - 1, x1, y1, hasPath);
    }

    path.Pop();                                                        //无路可走时,弹栈
}

bool isValid(vector<vector<int>>& map, int M, int N, int x1, int y1, int x2, int y2)
{
    if (x1 < 0 || x1 >= M || y1 < 0 || y1 >= N)
    {
        cout << "起始路径不在迷宫里，输入错误。";
    }
    else if (map[x1][y1] == 1)            //入口为墙
    {
        cout << "起始路径为墙,输入错误。";
    }
    else if (x2 < 0 || x2 >= M || y2 < 0 || y2 >= N)
    {
        cout << "终点不在迷宫里面，输入错误。";
    }
    else if (map[x2][y2] == 1)           //终点为墙
    {
        cout << "终点为墙,输入错误。";
    }
    else
    {
        return true;
    }
    return false;
}

int main()
{
    int M, N;
    cout << "先输入两个正整数,代表迷宫大小M * N:";
    cin >> M >> N;
    vector<vector<int>> map(M, vector<int>(N, 1));                  //初始化全为墙
    vector<vector<bool>> visited(M, vector<bool>(N, false));        //初始化为未访问过的
    Stack<pair<int, int>> path;
    
    cout << "创建迷宫地图，输入正整数0或1，分别代表迷宫的路和墙):" << endl;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int mapType;
            cin >> mapType;
            map[i][j] = mapType;
        }
    }
    cout << "输入入口坐标和出口坐标(x1, y1), (x2, y2):";
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    if (!isValid(map, M, N, x1, y1, x2, y2))
    {
        exit(1);
    }

    cout << "迷宫地图:(入口为[" << x1 << "," << y1 << "],出口为[" << x2 << "," << y2 << "])" << endl;

    cout << "      ";
    for (int i = 0; i < N; ++i)
    {
        cout << i << "列  ";
    }
    cout << endl;
    for (int i = 0; i < M; ++i)
    {
        cout << i << "行    ";
        for (int j = 0; j < N; ++j)
        {
            if (map[i][j] == 0)
            {
                cout << "0";
            }
            else
            {
                cout << "#";
            }
            cout << "    ";
        }
        cout << endl;
    }

    bool hasPath = false;
    //搜索
    DFS(map, visited, path, x1, y1, x2, y2, hasPath);
    if (!hasPath)
    {
        cout << "没有路径从入口[" << x1 << "," << y1 << "]到达出口[" << x2 << "," << y2 << "])" << endl;
    }

    system("pause");
    return 0;
}
