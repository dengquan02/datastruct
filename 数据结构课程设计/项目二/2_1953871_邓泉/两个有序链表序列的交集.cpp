#include <iostream>
#include "LinkedSet.h"

using namespace std;

//��֪�����ǽ�����������S1��S2����ƺ��������S1��S2�Ľ���������S3��

int main()
{
	LinkedSet S1, S2, S3;
	cout << "����������ǽ�������S1��S2��" << endl;
	S1.inputRear(-1);
	S2.inputRear(-1);
	S3 = S1 * S2;
	S3.output();

	system("pause");
	return 0;
}