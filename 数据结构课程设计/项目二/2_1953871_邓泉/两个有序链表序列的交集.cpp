#include <iostream>
#include "LinkedSet.h"

using namespace std;

//已知两个非降序链表序列S1和S2，设计函数构造出S1和S2的交集新链表S3。

int main()
{
	LinkedSet S1, S2, S3;
	cout << "请依次输入非降序序列S1和S2：" << endl;
	S1.inputRear(-1);
	S2.inputRear(-1);
	S3 = S1 * S2;
	S3.output();

	system("pause");
	return 0;
}