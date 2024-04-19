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
            reverse.Push(p);                                //��ջ��ת�������·��
            map[p.first][p.second] = 2;
        }

        cout << endl;
        cout << "      ";
        for (int i = 0; i < N; ++i)
        {
            cout << i << "��  ";
        }
        cout << endl;
        for (int i = 0; i < M; ++i)
        {
            cout << i << "��    ";
            for (int j = 0; j < N; ++j)
            {
                if (map[i][j] == 0)
                {
                    cout << "0";
                }
                else if (map[i][j] == 2)
                {
                    cout << "X";            //X����·��
                }
                else
                {
                    cout << "#";
                }
                cout << "    ";
            }
            cout << endl;
        }

        cout << endl << "�Թ�·��Ϊ:" << endl;
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

    path.Pop();                                                        //��·����ʱ,��ջ
}

bool isValid(vector<vector<int>>& map, int M, int N, int x1, int y1, int x2, int y2)
{
    if (x1 < 0 || x1 >= M || y1 < 0 || y1 >= N)
    {
        cout << "��ʼ·�������Թ���������";
    }
    else if (map[x1][y1] == 1)            //���Ϊǽ
    {
        cout << "��ʼ·��Ϊǽ,�������";
    }
    else if (x2 < 0 || x2 >= M || y2 < 0 || y2 >= N)
    {
        cout << "�յ㲻���Թ����棬�������";
    }
    else if (map[x2][y2] == 1)           //�յ�Ϊǽ
    {
        cout << "�յ�Ϊǽ,�������";
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
    cout << "����������������,�����Թ���СM * N:";
    cin >> M >> N;
    vector<vector<int>> map(M, vector<int>(N, 1));                  //��ʼ��ȫΪǽ
    vector<vector<bool>> visited(M, vector<bool>(N, false));        //��ʼ��Ϊδ���ʹ���
    Stack<pair<int, int>> path;
    
    cout << "�����Թ���ͼ������������0��1���ֱ�����Թ���·��ǽ):" << endl;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int mapType;
            cin >> mapType;
            map[i][j] = mapType;
        }
    }
    cout << "�����������ͳ�������(x1, y1), (x2, y2):";
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    if (!isValid(map, M, N, x1, y1, x2, y2))
    {
        exit(1);
    }

    cout << "�Թ���ͼ:(���Ϊ[" << x1 << "," << y1 << "],����Ϊ[" << x2 << "," << y2 << "])" << endl;

    cout << "      ";
    for (int i = 0; i < N; ++i)
    {
        cout << i << "��  ";
    }
    cout << endl;
    for (int i = 0; i < M; ++i)
    {
        cout << i << "��    ";
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
    //����
    DFS(map, visited, path, x1, y1, x2, y2, hasPath);
    if (!hasPath)
    {
        cout << "û��·�������[" << x1 << "," << y1 << "]�������[" << x2 << "," << y2 << "])" << endl;
    }

    system("pause");
    return 0;
}
