#include<iostream>
#include <string>
#include <unordered_map>
#include "LinkedStack.hpp"
#include "Calculator.h"

using namespace std;


//是否为操作数
bool isDigit(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return true;
    }
    return false;
}

//是否为单双目运算符
bool isOp(char ch)
{
    if (ch == '^' || ch == '%' || ch == '*' || ch == '/' || ch == '+' || ch == '-')
    {
        return true;
    }
    return false;
}

//检查表达式是否合法
bool isValid(const string& expr)
{
    int N = expr.length();

    if (N == 0)
    {
        cerr << "表达式为空！" << endl;
        return false;
    }
    for (int i = 0; i < N; i++)
    {
        if (!(isDigit(expr[i]) || isOp(expr[i]) || expr[i] == '=' || expr[i] == '(' || expr[i] == ')'))
        {
            cerr << "表达式中含有非法字符!" << endl;
            return false;
        }

        if (expr[i] == ')')
        {
            int leftCount = 0, rightCount = 0;      //left记录（的个数, right记录）的个数
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
                cerr << "未找到左括号匹配右括号!" << endl;
                return false;
            }
        }
        if (expr[i] == '(')
        {
            if (expr.find(')', i) == -1)
            {
                cerr << "未找到右括号匹配左括号！" << endl;
                return false;
            }
        }

        if (expr[i] == ')' && i - 1 >= 0 && expr[i - 1] == '(')
        {
            cerr << "表达式中存在()内为空！" << endl;
            return false;
        }
        
        if (i != N - 1)
        {
            if (expr[i] == '=')
            {
                cerr << "表达式非末尾端出现了 = ！" << endl;
                return false;
            }
        }
        else
        {
            if (expr[i] != '=')
            {
                cerr << "表达式没有以 = 结尾！" << endl;
                return false;
            }
        }

        //单目
        if ((expr[i] == '+' || expr[i] == '-') && (i == 0 || expr[i - 1] == '('))     //单目运算符只可能出现在开头或者（右边
        {
            if (!(i + 1 < N && (expr[i + 1] == '(' || isDigit(expr[i + 1]))))     //后面没有接操作数或者 (
            {
                cerr << "单目运算符 + - 不合理 ！" << endl;
                return false;
            }
        }
        //双目
        else if (isOp(expr[i]))
        {
            if (!(i - 1 >= 0 && i + 1 < N && ((expr[i - 1] == ')' || isDigit(expr[i - 1])) && (expr[i + 1] == '(' || isDigit(expr[i + 1])))))
            {
                cerr << "双目运算符 + - * / % ^ 不合理!" << endl;
                return false;
            }
        }
    }
    return true;
}



//从expr的i位置读入操作数,如果输入大于0-9的数字也能正确处理
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
    postExpr += expr.substr(i, j - i);          //数字的字符串
    postExpr += " ";
    i = j - 1;                                  //更新i值
}


//从中序到后序
string toPostOrder(const string& expr)
{
    int N = expr.length();

    unordered_map<char, int> priority;      //map数组存储运算符的优先级
    priority['='] = 1;
    priority['('] = 2;
    priority[')'] = 2;
    priority['+'] = 3;
    priority['-'] = 3;
    priority['*'] = 4;
    priority['/'] = 4;
    priority['%'] = 5;
    priority['^'] = 6;

    string postExpr;         //存储后序表达式的字符串
    LinkedStack<char> s;           //运算符栈
    for (int i = 0; i < N; ++i)
    {
        if ((expr[i] == '+' || expr[i] == '-') && (i == 0 || expr[i - 1] == '(')) //单目运算符
        {
            if (expr[i] == '-') 
            {
                postExpr += "0 ";
                EnDigit(expr, postExpr, ++i);      //将 - 后面的操作数读入
                postExpr += "- ";
            }
        }
        else if (isDigit(expr[i]))      //操作数直接加入字符串
        {
            EnDigit(expr, postExpr, i);
        }

        else if (expr[i] == '(')        //左括号
        {
            s.Push(expr[i]);
        }
        else if (expr[i] == ')')        //右括号
        {
            char top; s.getTop(top);
            while (top != '(')
            {
                postExpr += top;
                postExpr += " ";
                s.Pop();
                s.getTop(top);
            }
            s.Pop();         //弹出(
        }

        else                        //运算符
        {
            if (s.isEmpty())          //栈为空,直接压入即可
            {
                s.Push(expr[i]);
            }
            else
            {
                //与栈顶运算符比较优先级
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
                            s.getTop(top);      //栈顶变化，需要更新
                        }
                    }
                    s.Push(expr[i]);
                }
            }
        }
    }

    //剩下的运算符一起加上
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
    string inExpr;                                //输入的中序表达式
    Calculator CALC;
    char choice;
    do
    {
        cout << "请输入表达式：" << endl;
        getline(cin, inExpr);
        if (isValid(inExpr))
        {
            string postExpr = toPostOrder(inExpr);
            cout << "后序表达式为:" << postExpr << endl;
            double result = CALC.Run(postExpr);
            cout << "运算结果为：" << result << endl;
        }
        cout << "是否继续（y,n）？";
        cin >> choice;
        cin.get();              //用于吃掉空格
    } while (choice == 'y');

    system("pause");
    return 0;
}
