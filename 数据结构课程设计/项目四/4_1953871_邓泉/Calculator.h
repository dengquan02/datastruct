#pragma once
#include <iostream>
#include <math.h>
#include <string>
#include "LinkedStack.hpp"
using namespace std;



class Calculator
{
public:

	//执行表达式计算
	double Run(string& postExpr);

private:
	LinkedStack<double> s;								//栈
	void AddOperand(double value);						//进操作数栈
	bool get_2_Operands(double& left, double& right);	//从栈中退出两个操作数
	void DoOperator(char op);							//形成运算指令，进行计算
};
