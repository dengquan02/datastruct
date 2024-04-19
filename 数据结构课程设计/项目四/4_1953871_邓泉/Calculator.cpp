#include "Calculator.h"


//�Ӳ�����ջ��ȡ������������
bool Calculator::get_2_Operands(double& left, double& right)
{
	if (s.isEmpty())
	{
		cerr << "ȱ���Ҳ�������" << endl;
		return false;
	}
	s.Pop(right);

	if (s.isEmpty())
	{
		cerr << "ȱ�����������" << endl;
		return false;
	}
	s.Pop(left);

	return true;
}


//��������ֵvalue����ջ
void Calculator::AddOperand(double value)
{
	s.Push(value);
}



//ȡ���������������ݲ�����op�γ�����ָ�����
void Calculator::DoOperator(char op)
{
	double left, right, value;
	int result = get_2_Operands(left, right);			//ȡ����������
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
				cerr << "����Ϊ��!" << endl;
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


//��һ����׺���ʽ��ֵ�����ַ���=������
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
			//���Ǵ���0-9�Ĳ�����
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
			s.Push(atoi(postExpr.substr(i, j - i).c_str()));	//postExpr.substr(i, j - i); �õ������ֵ��ַ���
			i = j - 1;
		}
	}
	double value;
	s.getTop(value);
	return value;
}