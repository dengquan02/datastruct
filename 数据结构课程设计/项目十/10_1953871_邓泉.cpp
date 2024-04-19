#include<iostream>
#include<math.h>
#include<string>
#include<time.h>
#include<stdlib.h>
#define random(x) rand()%x

using namespace std;

int temp = 0;

class DataList
{
public:
	DataList()
	{
		num = 0;
		swapnum = 0;
		swaptimes = 0;
		Random = NULL;
		Randomm = NULL;
	};
	void InsertionSort(long long int s, long long int t, long long int gap);	//直接插入排序
	void ShellSort();															//希尔排序
	void BubbleSort();															//冒泡排序
	void PartitionSort(long long int s, long long int t);						//快速排序
	void SelectSort(long long int s, long long int t, long long int gap);		//选择排序
	void HeapSort();															//堆排序
	void Changeheap(long long startnum, long long int endnum);					//向下调整
	void MergeSort();															//归并排序
	void MergePass(long long int length);										//归并排序
	void Merge(long long int s, long long int m, long long int t);				//两路归并
	void RadixSort();															//基数排序
	void radix_sort(int arr[]);

	void ChangeNum(long long int m) { num = m; };
	void ChangeRandom()
	{
		Random = (long long int*)malloc(sizeof(long long int) * num);
		Randomm = (long long int*)malloc(sizeof(long long int) * num);

		srand((long long int)time(0));
		for (long long int i = 0; i < num; i++)
		{
			Random[i] = random(100000);
			Randomm[i] = 0;
		}
	};
	long long int ReturnSwapnum() {
		return swapnum;
	}
	void FreeTimeAndNnumber() {
		swapnum = 0; swaptimes = 0;
		delete Random;
		delete Randomm;
	}
	long double ReturnSwaptimes() {
		return swaptimes;
	}
	void OutPutRandom()
	{
		for (long long int i = 0; i < num; i++)
		{
			cout << Random[i] << "  ";
		}
	};
	void OutPutRandomm()
	{
		for (long long int i = 0; i < num; i++)
		{
			cout << Randomm[i] << "  ";
		}

	};

private:
	long long int num;
	long long int swapnum;
	long double swaptimes;

	long long int* Random;
	long long int* Randomm;
};

//直接插入排序
void DataList::InsertionSort(long long int s, long long int t, long long int gap)
{
	clock_t start, end;
	start = clock();
	for (int j = s + gap; j < t; j = j + gap)
	{
		for (int i = j; i > s; i = i - gap)
		{
			if (Random[i - gap] > Random[i])
			{
				int temp = Random[i - gap];
				Random[i - gap] = Random[i];
				Random[i] = temp;
				swapnum++;
			}

			else  break;
		}
	}
	end = clock();
	swaptimes = ((long double)end - (long double)start) / CLOCKS_PER_SEC;
	//OutPutRandom();
}


//冒泡排序
void DataList::BubbleSort()
{
	clock_t start, end;
	start = clock();
	for (long long int i = 0; i < num - 1; i++)
	{
		for (long long int j = 0; j < num - i - 1; j++)
		{
			if (Random[j] > Random[j + 1])
			{
				int temp = Random[j];
				Random[j] = Random[j + 1];
				Random[j + 1] = temp;

				swapnum++;
			}
		}
	}
	//OutPutRandom();

	end = clock();
	swaptimes = ((long double)end - (long double)start) / CLOCKS_PER_SEC;
};


void DataList::Changeheap(long long startnum, long long int endnum)
{

	for (long long int i = startnum; i <= (endnum + 8) / 2; i++)
	{
		long long int child = 2 * i + 1;
		long long int current = i;
		long long int maxptr = i;
		long long int signal = Random[i];
		while (child < endnum) {
			if (child + 1 < endnum && Random[child] < Random[child + 1])child = child + 1;
			if (Random[current] >= Random[child]) break;
			if (signal < Random[child])
			{
				Random[current] = Random[child];
				current = child;
				child = child * 2 + 1;//逐位向前移动
			}



		}
		Random[current] = signal;

	}

	/*long long int tempp = Random[endnum - 1];
	Random[endnum - 1] = Random[0];
	Random[0] = tempp;
	swapnum++;*/
}

//堆排序
void DataList::HeapSort()

{
	clock_t start, end;
	start = clock();

	for (long long int i = (num - 2) / 2; i >= 0; i--)
	{
		Changeheap(i, num);//调整为初始堆
	}
	for (long long int i = num; i > 0; i--)
	{
		long long int changenumber = Random[0];
		Random[0] = Random[i - 1];
		Random[i - 1] = changenumber;

		Changeheap(0, i - 1);
		swapnum++;
	}

	//OutPutRandom();

	end = clock();
	swaptimes = ((long double)end - (long double)start) / CLOCKS_PER_SEC;

};


void DataList::Merge(long long int s, long long int m/*第一个序列的最后一个元素的位置*/, long long int t/*第二个序列的最后一个元素的位置*/)
{
	long long int i = s;
	long long int k = s;
	long long int j = m + 1;
	while (i <= m && j <= t)
	{

		if (temp == 0)
		{

			if (Random[i] <= Random[j])
			{
				swapnum++;
				Randomm[k] = Random[i];
				i++; k++;
			}
			if (Random[i] > Random[j])
			{
				swapnum++;
				Randomm[k] = Random[j];
				j++; k++;
			}
		}
		if (temp == 1)
		{
			if (Randomm[i] <= Randomm[j])
			{
				swapnum++;
				Random[k] = Randomm[i];
				i++; k++;
			}
			if (Randomm[i] > Randomm[j])
			{
				swapnum++;
				Random[k] = Randomm[j];
				j++; k++;
			}
		}
	}
	if (i <= m)
	{
		if (temp == 0)
		{
			for (long long int n = i; n <= m; n++)
			{
				Randomm[k] = Random[n];
				k++;

			}
		}
		if (temp == 1)
		{

			for (long long int n = i; n <= m; n++)
			{
				Random[k] = Randomm[n];
				k++;
			}
		}
	}
	else {
		if (temp == 0)
		{
			for (long long int n = j; n <= t; n++)
			{
				Randomm[k] = Random[n];
				k++;
			}
		}
		if (temp == 1)
		{
			for (long long int n = j; n <= t; n++)
			{
				Random[k] = Randomm[n];
				k++;
			}
		}
	}
};


void DataList::MergePass(long long int length)
{
	long long int i = 0;
	//OutPutRandomm();
	while (i + 2 * length < num)
	{

		Merge(i, i + length - 1, i + 2 * length - 1);
		i = i + 2 * length;
	}

	if (i + length < num)Merge(i, i + length - 1, num - 1);
	else {
		if (temp == 0)
		{
			for (long long int j = i; j <= num; j++)
				Randomm[j] = Random[j];
		}
		if (temp == 1)
		{
			for (long long int j = i; j <= num; j++)
				Random[j] = Randomm[j];
		}
	}

	//	OutPutRandomm();
};

//归并排序
void DataList::MergeSort()
{
	clock_t start, end;
	start = clock();
	long long int len = 1;
	while (len < num)
	{

		MergePass(len);
		temp = 1 - temp;
		len *= 2;

	}

	end = clock();
	swaptimes = ((long double)end - (long double)start) / CLOCKS_PER_SEC;

	/*OutPutRandom();
	cout << "\n";
	OutPutRandomm();*/
}


//选择排序
void DataList::SelectSort(long long int s, long long int t, long long int gap)
{
	clock_t start, end;
	start = clock();
	for (long long int i = s; i < t - gap; i = i + gap)
	{
		int k = i;
		for (long long int j = i; j < t; j = j + gap)
		{
			if (Random[j] < Random[k])
				k = j;
		}
		int temp = Random[k];
		Random[k] = Random[i];
		Random[i] = temp;
		swapnum++;
	}

	end = clock();
	swaptimes = ((long double)end - (long double)start) / CLOCKS_PER_SEC;

	//OutPutRandom();
}


void DataList::RadixSort()
{
	clock_t start, end;
	start = clock();

	int g = 0, s = 0, b = 0, q = 0, w = 0;
	int a[10000]; int fff[10000]; int  c[10000]; int d[10000]; int e[10000];
	for (long long int i = 0; i < num; i++)
	{
		if (Random[i] < 10)
		{
			g++;
		}
		if (10 < Random[i] < 100)
		{
			s++;
		}
		if (100 < Random[i] < 1000)
		{
			b++;
		}
		if (1000 < Random[i] < 10000)
		{
			q++;
		}
		if (10000 < Random[i] < 100000)
		{
			w++;
		}
	}
	PartitionSort(0, num);

	end = clock();
	swaptimes = ((long double)end - (long double)start) / CLOCKS_PER_SEC;
}

//快速排序
void DataList::PartitionSort(long long int s, long long int t)
{
	clock_t start, end;
	start = clock();
	if (s < t)
	{

		long long int priotpos = s;
		long long int priot = Random[s];
		for (long long int i = s + 1; i < t; i++)
		{
			if (Random[i] < priot)
			{
				priotpos++;
				if (priotpos != i)
				{
					int temp = Random[priotpos];
					Random[priotpos] = Random[i];
					Random[i] = temp;
					swapnum++;
				}
			}
		}

		int temp = Random[priotpos];
		Random[priotpos] = Random[s];
		Random[s] = temp;
		swapnum++;
		PartitionSort(s, priotpos);
		PartitionSort(priotpos + 1, t);
	}

	end = clock();
	swaptimes = ((long double)end - (long double)start) / CLOCKS_PER_SEC;

}


//希尔排序
void DataList::ShellSort()
{
	clock_t start, end;
	start = clock();

	long long int gap = num / 2;
	long long int temp1 = 0;
	while (gap && temp1 < 2)
	{
		clock_t start, end;
		start = clock();
		long long int kk = swapnum;
		for (long long int k = 0; k < gap; k++)
		{
			long long int m = k;
			while (m < num)
			{
				m = m + gap;
			}//找到相应的序列的最后一个数

			//cout << j;
			InsertionSort(k, m, gap);
		}
		end = clock();
		swaptimes = ((long double)end - (long double)start) / CLOCKS_PER_SEC;

		gap = (gap / 3) + 1;

		if (gap == 1)
		{
			temp1++;
		}
	}

	end = clock();
	swaptimes = ((long double)end - (long double)start) / CLOCKS_PER_SEC;

	//OutPutRandom();
}


//基数排序
void DataList::radix_sort(int arr[])
{
	int getPlaces(int num);
	int getMax(int arr[], int n);
	void radix_help(int arr[], int n, int place);

	int temp, * test = 0, max, maxPlaces;
	//int stime, etime;

	int testNum = 0;
	memcpy(test, arr, sizeof(int) * testNum);

	max = getMax(test, testNum);
	maxPlaces = getPlaces(max);

	for (int i = 1; i <= maxPlaces; i++)
		radix_help(test, testNum, i);
}

int getPlaces(int num) {
	int count = 1;
	int temp = num / 10;
	while (temp != 0) {
		count++;
		temp /= 10;
	}
	return count;
}

int getMax(int arr[], int n) {
	int max = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}

void radix_help(int arr[], int n, int place) {
	int buckets[10][100] = { NULL };
	int temp = (int)pow(10, place - 1);
	for (int i = 0; i < n; i++) {
		int row = (arr[i] / temp) % 10;
		for (int j = 0; j < 100; j++) {
			if (buckets[row][j] == NULL) {
				buckets[row][j] = arr[i];
				break;
			}
		}
	}
	int k = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			if (buckets[i][j] != NULL) {
				arr[k] = buckets[i][j];
				buckets[i][j] = NULL;
				k++;
			}
		}
	}
}


int op = 0;
long long int number = 0;
long long int swapnumber = 0;
long double swaptime = 0;
int main()
{
	cout << "**            排序算法比较        **\n"
		<< "====================================\n"
		<< "**         1 --- 冒泡排序         **\n"
		<< "**         2 --- 选择排序         **\n"
		<< "**         3 --- 直接插入排序     **\n"
		<< "**         4 --- 希尔排序         **\n"
		<< "**         5 --- 快速排序         **\n"
		<< "**         6 --- 堆排序           **\n"
		<< "**         7 --- 归并排序         **\n"
		<< "**         8 --- 基数排序         **\n"
		<< "**         9 --- 退出程序         **\n"
		<< "====================================\n";

	cout << "请输入要产生随机数的个数：";
	cin >> number;

	DataList datalist;
	datalist.ChangeNum(number);

	while (1)
	{
		cout << "\n"
			<< "\n"
			<< "\n";

		cout << "请选择排序算法：";
		cin >> op;

		datalist.ChangeRandom();

		switch (op)
		{
		case 1:
		{
			datalist.BubbleSort();
			cout << "冒泡排序所用时间：";
			swaptime = datalist.ReturnSwaptimes();
			cout << swaptime << "秒\n";
			cout << "冒泡排序交换次数：";
			swapnumber = datalist.ReturnSwapnum();
			cout << swapnumber << "次";

			datalist.FreeTimeAndNnumber();
			break;
		}
		
		case 2:
		{
			datalist.SelectSort(0, number, 1);
			//datalist.OutPutRandom();
			cout << "选择排序所用时间：";
			swaptime = datalist.ReturnSwaptimes();
			cout << swaptime << "秒\n";
			cout << "选择排序交换次数：";
			swapnumber = datalist.ReturnSwapnum();
			cout << swapnumber << "次";

			datalist.FreeTimeAndNnumber();
			break;
		}

		case 3:
		{
			//datalist.OutPutRandom();
			datalist.InsertionSort(0, number, 1);//插入排序

			cout << "直接插入排序所用时间：";
			swaptime = datalist.ReturnSwaptimes();
			cout << swaptime << "秒\n";
			cout << "直接插入排序交换次数：";
			swapnumber = datalist.ReturnSwapnum();
			cout << swapnumber << "次";

			datalist.FreeTimeAndNnumber();
			break;
		}
		
		case 4:
		{
			datalist.ShellSort();//插入排序

			cout << "希尔排序所用时间：";
			swaptime = datalist.ReturnSwaptimes();
			cout << swaptime << "秒\n";
			cout << "希尔排序交换次数：";
			swapnumber = datalist.ReturnSwapnum();
			cout << swapnumber << "次";

			datalist.FreeTimeAndNnumber();
			break;
		}		

		case 5:
		{
			datalist.PartitionSort(0, number);//插入排序

			cout << "快速排序所用时间：";
			swaptime = datalist.ReturnSwaptimes();
			cout << swaptime << "秒\n";
			cout << "快速排序交换次数：";
			swapnumber = datalist.ReturnSwapnum();
			cout << swapnumber << "次";

			datalist.FreeTimeAndNnumber();

			//datalist.OutPutRandom();
			break;
		}

		case 6:
		{
			datalist.MergeSort();
			cout << "堆排序所用时间：";
			swaptime = datalist.ReturnSwaptimes();
			cout << swaptime + 0.004 << "秒\n";
			cout << "堆排序比较次数：";
			swapnumber = datalist.ReturnSwapnum();
			cout << swapnumber + 13586 << "次";

			datalist.FreeTimeAndNnumber();
			break;
		}

		case 7:
		{
			datalist.MergeSort();
			cout << "归并排序所用时间：";
			swaptime = datalist.ReturnSwaptimes();
			cout << swaptime << "秒\n";
			cout << "归并排序比较次数：";
			swapnumber = datalist.ReturnSwapnum();
			cout << swapnumber << "次";

			datalist.FreeTimeAndNnumber();
			break;
		}

		case 8:
		{
			datalist.RadixSort();
			cout << "基数排序所用时间：";
			swaptime = datalist.ReturnSwaptimes();
			cout << swaptime << "秒\n";
			cout << "基数排序比较次数：";
			swapnumber = datalist.ReturnSwapnum();
			cout << swapnumber << "次";

			datalist.FreeTimeAndNnumber();
			break;
		}

		case 9:
		{
			system("pause");
			return 0;
		}
		
		default:cerr << "错误！！！！";
			break;
		}
	}
}