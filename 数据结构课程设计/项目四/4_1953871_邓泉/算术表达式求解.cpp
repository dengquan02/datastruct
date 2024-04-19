#include<iostream>
#include <string>
#include <unordered_map>
#include "LinkedStack.hpp"
#include "Calculator.h"

using namespace std;


//�Ƿ�Ϊ������
bool isDigit(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return true;
    }
    return false;
}

//�Ƿ�Ϊ��˫Ŀ�����
bool isOp(char ch)
{
    if (ch == '^' || ch == '%' || ch == '*' || ch == '/' || ch == '+' || ch == '-')
    {
        return true;
    }
    return false;
}

//�����ʽ�Ƿ�Ϸ�
bool isValid(const string& expr)
{
    int N = expr.length();

    if (N == 0)
    {
        cerr << "���ʽΪ�գ�" << endl;
        return false;
    }
    for (int i = 0; i < N; i++)
    {
        if (!(isDigit(expr[i]) || isOp(expr[i]) || expr[i] == '=' || expr[i] == '(' || expr[i] == ')'))
        {
            cerr << "���ʽ�к��зǷ��ַ�!" << endl;
            return false;
        }

        if (expr[i] == ')')
        {
            int leftCount = 0, rightCount = 0;      //left��¼���ĸ���, right��¼���ĸ���
            for (int j = 0; j <= i; j++)
            {
                if (expr[j] == ')')
                {
                    rightCount++;
                }
                else if (expr[j] == '(')
                {
                    leftCount++;
                }
            }
            if (rightCount > leftCount)
            {
                cerr << "δ�ҵ�������ƥ��������!" << endl;
                return false;
            }
        }
        if (expr[i] == '(')
        {
            if (expr.find(')', i) == -1)
            {
                cerr << "δ�ҵ�������ƥ�������ţ�" << endl;
                return false;
            }
        }

        if (expr[i] == ')' && i - 1 >= 0 && expr[i - 1] == '(')
        {
            cerr << "���ʽ�д���()��Ϊ�գ�" << endl;
            return false;
        }
        
        if (i != N - 1)
        {
            if (expr[i] == '=')
            {
                cerr << "���ʽ��ĩβ�˳����� = ��" << endl;
                return false;
            }
        }
        else
        {
            if (expr[i] != '=')
            {
                cerr << "���ʽû���� = ��β��" << endl;
                return false;
            }
        }

        //��Ŀ
        if ((expr[i] == '+' || expr[i] == '-') && (i == 0 || expr[i - 1] == '('))     //��Ŀ�����ֻ���ܳ����ڿ�ͷ���ߣ��ұ�
        {
            if (!(i + 1 < N && (expr[i + 1] == '(' || isDigit(expr[i + 1]))))     //����û�нӲ��������� (
            {
                cerr << "��Ŀ����� + - ������ ��" << endl;
                return false;
            }
        }
        //˫Ŀ
        else if (isOp(expr[i]))
        {
            if (!(i - 1 >= 0 && i + 1 < N && ((expr[i - 1] == ')' || isDigit(expr[i - 1])) && (expr[i + 1] == '(' || isDigit(expr[i + 1])))))
            {
                cerr << "˫Ŀ����� + - * / % ^ ������!" << endl;
                return false;
            }
        }
    }
    return true;
}



//��expr��iλ�ö��������,����������0-9������Ҳ����ȷ����
void EnDigit(const string& expr, string& postExpr, int& i)
{
    int j = i + 1;
    while (true)
    {
        if (j < (int)expr.length() && isDigit(expr[j]))
        {
            j++;
        }
        else
        {
            break;
        }
    }
    postExpr += expr.substr(i, j - i);          //���ֵ��ַ���
    postExpr += " ";
    i = j - 1;                                  //����iֵ
}


//�����򵽺���
string toPostOrder(const string& expr)
{
    int N = expr.length();

    unordered_map<char, int> priority;      //map����洢����������ȼ�
    priority['='] = 1;
    priority['('] = 2;
    priority[')'] = 2;
    priority['+'] = 3;
    priority['-'] = 3;
    priority['*'] = 4;
    priority['/'] = 4;
    priority['%'] = 5;
    priority['^'] = 6;

    string postExpr;         //�洢������ʽ���ַ���
    LinkedStack<char> s;           //�����ջ
    for (int i = 0; i < N; ++i)
    {
        if ((expr[i] == '+' || expr[i] == '-') && (i == 0 || expr[i - 1] == '(')) //��Ŀ�����
        {
            if (expr[i] == '-') 
            {
                postExpr += "0 ";
                EnDigit(expr, postExpr, ++i);      //�� - ����Ĳ���������
                postExpr += "- ";
            }
        }
        else if (isDigit(expr[i]))      //������ֱ�Ӽ����ַ���
        {
            EnDigit(expr, postExpr, i);
        }

        else if (expr[i] == '(')        //������
        {
            s.Push(expr[i]);
        }
        else if (expr[i] == ')')        //������
        {
            char top; s.getTop(top);
            while (top != '(')
            {
                postExpr += top;
                postExpr += " ";
                s.Pop();
                s.getTop(top);
            }
            s.Pop();         //����(
        }

        else                        //�����
        {
            if (s.isEmpty())          //ջΪ��,ֱ��ѹ�뼴��
            {
                s.Push(expr[i]);
            }
            else
            {
                //��ջ��������Ƚ����ȼ�
                char top; s.getTop(top);
                if (priority[expr[i]] > priority[top])
                {
                    s.Push(expr[i]);
                }
                else
                {
                    while (!s.isEmpty() && priority[expr[i]] <= priority[top])
                    {
                        postExpr += top;
                        postExpr += " ";
                        s.Pop();
                        if (!s.isEmpty())
                        {
                            s.getTop(top);      //ջ���仯����Ҫ����
                        }
                    }
                    s.Push(expr[i]);
                }
            }
        }
    }

    //ʣ�µ������һ�����
    while (!s.isEmpty())
    {
        char top; s.getTop(top);
        if (top != '=')
        {
            postExpr += top;
            postExpr += " ";
        }
        s.Pop();
    }

    return postExpr;
}



int main()
{ 
    string inExpr;                                //�����������ʽ
    Calculator CALC;
    char choice;
    do
    {
        cout << "��������ʽ��" << endl;
        getline(cin, inExpr);
        if (isValid(inExpr))
        {
            string postExpr = toPostOrder(inExpr);
            cout << "������ʽΪ:" << postExpr << endl;
            double result = CALC.Run(postExpr);
            cout << "������Ϊ��" << result << endl;
        }
        cout << "�Ƿ������y,n����";
        cin >> choice;
        cin.get();              //���ڳԵ��ո�
    } while (choice == 'y');

    system("pause");
    return 0;
}
