#pragma once
#include <iostream>
#include <math.h>
#include <string>
#include "LinkedStack.hpp"
using namespace std;



class Calculator
{
public:

	//ִ�б��ʽ����
	double Run(string& postExpr);

private:
	LinkedStack<double> s;								//ջ
	void AddOperand(double value);						//��������ջ
	bool get_2_Operands(double& left, double& right);	//��ջ���˳�����������
	void DoOperator(char op);							//�γ�����ָ����м���
};
