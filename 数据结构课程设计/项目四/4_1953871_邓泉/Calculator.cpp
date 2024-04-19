#include "Calculator.h"


//从操作数栈中取出两个操作数
bool Calculator::get_2_Operands(double& left, double& right)
{
	if (s.isEmpty())
	{
		cerr << "缺少右操作数！" << endl;
		return false;
	}
	s.Pop(right);

	if (s.isEmpty())
	{
		cerr << "缺少左操作数！" << endl;
		return false;
	}
	s.Pop(left);

	return true;
}


//操作数的值value进入栈
void Calculator::AddOperand(double value)
{
	s.Push(value);
}



//取两个操作数，根据操作符op形成运算指令并计算
void Calculator::DoOperator(char op)
{
	double left, right, value;
	int result = get_2_Operands(left, right);			//取两个操作数
	if (result)
	{
		switch (op)
		{
		case'^':
			value = pow(left, right); AddOperand(value); break;
		case'*':
			value = left * right; AddOperand(value); break;
		case'%':
			value = (int)left % (int)right; AddOperand(value); break;
		case'/':
			if (right == 0)
			{
				cerr << "除数为零!" << endl;
				s.makeEmpty();
			}
			else
			{
				value = left / right;
				AddOperand(value);
			}
			break;
		case'+':
			value = left + right; AddOperand(value); break;
		case'-':
			value = left - right; AddOperand(value); break;
		}
	}
	else
	{
		s.makeEmpty();
	}
}


//求一个后缀表达式的值，以字符‘=’结束
double Calculator::Run(string& postExpr)
{
	s.makeEmpty();
	int N = postExpr.length();

	for (int i = 0; i < N; i += 2)
	{
		char ch = postExpr[i];
		if (ch == '^' || ch == '%' || ch == '*' || ch == '/' || ch == '+' || ch == '-')
		{
			DoOperator(ch);
		}
		else
		{
			//考虑大于0-9的操作数
			int j = i + 1;
			while (true)
			{
				if (j < N && (postExpr[j] <= '9' && postExpr[j] >= '0'))
				{
					j++;
				}
				else
				{
					break;
				}
			}
			s.Push(atoi(postExpr.substr(i, j - i).c_str()));	//postExpr.substr(i, j - i); 得到了数字的字符串
			i = j - 1;
		}
	}
	double value;
	s.getTop(value);
	return value;
}