#include<iostream>
#include<fstream>
#include<sstream>
#include<Windows.h>
#include<iomanip>
#include<limits.h>
#include<io.h>
using namespace std;

#define MAX_SIZE 50

#define MaxTerm 10//每学期最多课程数


class Edge
{
public:
	Edge() { head = tail = value = 0; };
	Edge(int h, int t, int v) :head(h), tail(t), value(v) {};//含参构造函数
	bool operator<(const Edge& p) { return this->value < p.value; }
	bool operator>(const Edge& p) { return this->value > p.value; }
	int head;//起点
	int tail;//终点
	int value;//边的权值
};


struct Course
{
	Course() :period(0), term(0) {};
	Course(string pnum, string pname, int p, int t) :num(pnum), name(pname), period(p), term(t) {};
	bool operator==(const Course& pcourse) { return this->num == pcourse.num; }
	string operator=(const Course& pcourse) { num = pcourse.num; name = pcourse.name; period = pcourse.period; term = pcourse.term; return name; }
	string num;//课程编号
	string name;//课程名称
	int period;//学时
	int term;//指定开课学期，若为0则电脑自动排课
};

class ClassList
{
private:
	int maxsize;//最大数组大小
	int size;//当前数组大小

public:
	Course* data;//存放数据的数组
	ClassList() :maxsize(MAX_SIZE), size(0) { data = new Course[maxsize + 1]; }//构造函数
	~ClassList() { delete[] data; }//析构函数
	void insert(Course& t)//插入元素
	{
		data[size] = t;
		size++;
	}
	void remove(Course& t)//删除元素
	{
		int i = find(t);
		for (int j = i; j < size - 1; j++)
		{
			data[j] = data[j + 1];
		}
		size--;
	}
	int find(Course& t)//查找该元素存放在数组的位置
	{
		for (int i = 0; i < size; i++)
		{
			if (data[i] == t) return i;
		}
		return -1;
	}
};

//图的类实现


class Graph
{
private:
	int maxsize;//顶点个数上限
	int verticenum;//当前的顶点数
	int edgenum;//当前的边数
	int** edge;//邻接矩阵
	ClassList* List;//存放顶点的列表
	int* count;//表示各顶点的入度
public:
	Graph() :maxsize(MAX_SIZE), verticenum(0), edgenum(0)//构造函数
	{
		edge = new int* [maxsize];
		for (int i = 0; i < maxsize; i++)
		{
			edge[i] = new int[maxsize];
		}
		for (int i = 0; i < maxsize; i++) {
			for (int j = 0; j < maxsize; j++) {
				edge[i][j] = -1;
			}
		}

		List = new ClassList;

		count = new int[maxsize];
		for (int i = 0; i < maxsize; i++) count[i] = 0;
	}
	~Graph()//析构函数
	{
		delete List;
		for (int i = 0; i < maxsize; i++) delete[] edge[i];
		delete[] edge;
		delete[] count;
	}
	void AddEdge(Course h, Course t, int v = 1);//添加边
	void AddVertice(Course node);//添加顶点
	void DeleteVertice(Course node);//删除顶点
	int EdgeNum() const { return edgenum; }//返回边的个数
	int size() const { return verticenum; }//返回顶点的个数
	ClassList* list() const { return List; }//返回顶点列表
	int* Count() const { return count; }//返回count数组指针

};

void Graph::AddEdge(Course  h, Course t, int v)
{
	if (v < 0)
	{
		cout << "边的权值不合法！！！！" << endl;
		return;
	}//权值必须是正数

	int i = List->find(h), j = List->find(t);
	if (i >= 0 && j >= 0)
	{
		edge[i][j] = v;
	}
	else
	{
		cout << "未查找到边的顶点，添加边失败！！！！" << endl;
		return;
	}
	edgenum++;
	count[j]++;

}

void Graph::AddVertice(Course node)
{
	if (verticenum == maxsize)
	{
		cerr << "Graph is full." << endl;
		return;
	}
	List->insert(node);
	verticenum++;
}



void Graph::DeleteVertice(Course node)
{
	int i = List->find(node);

	for (int j = 0; j < size(); j++)
	{
		if (edge[i][j] > 0) count[j]--;
	}//如有从i到j的有向边，则j的入度减一

	for (int j = i; j < size() - 1; j++) {
		for (int k = 0; k < size(); k++) {
			edge[j][k] = edge[j + 1][k];
			edge[k][j] = edge[k][j + 1];
		}
	}//将邻接矩阵平移

	for (int j = i; j < size() - 1; j++)
	{
		count[j] = count[j + 1];
	}//count数组平移

	verticenum--;
	List->remove(node);
}



Graph Courses;//包含所有课程的图

int coursenum[MaxTerm];//每学期指定的课程数

inline int StrToInt(string& str)//string到int的转换
{
	int len = str.length();
	int base = 1;
	int ans = 0;

	for (int i = len - 1; i >= 0; i--)
	{
		ans += (str[i] - '0') * base;
		base *= 10;
	}
	return ans;
}

Course* GetFromNum(const string& num)//根据课程的编号搜索已有课程
{
	Course* p = Courses.list()->data;
	int size = Courses.size();
	while (size--)
	{
		if (p->num == num) return p;
		p++;
	}
	return NULL;
}



bool GetData(ifstream& infile, int& num)//从文件读入数据，并存入图中
{
	if (!infile.is_open())
	{
		cerr << "无法打开文件" << endl;
		return false;
	}

	int k = 0, count = 0;
	while (infile >> coursenum[k])//输入每学期上的课程数
	{
		count += coursenum[k];
		k++;
		if (infile.get() == '\n') break;
	}

	string data[10];
	int i = 0;
	while (infile >> data[i++])
	{
		if (infile.get() == '\n')//换行前，构建有向边
		{
			int period = StrToInt(data[2]), term = StrToInt(data[3]);


			Course cur(data[0], data[1], period, term);
			Courses.AddVertice(cur);
			for (int j = 4; j < i; j++)
			{
				Course* p = GetFromNum(data[j]);
				Courses.AddEdge(*p, cur);
			}
			num++;
			i = 0;
		}
	}

	if (count != num) return false;
	else return true;
}


string Table[4][5];
bool ifcourse[4][5];


int currentval;
int bestval;
int current[4][3];
int best[4][3];


void TableClear()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			ifcourse[i][j] = 0;
		}
	}
}


//权值函数
int Value(int n)
{
	int value = 0;

	for (int i = 0; i <= n; i++)
	{
		if (current[i][2] == 1) value -= 100;
		if (current[i][0] == 0 || current[i][0] == 2) value += 1;
		else value = value + 5;

		for (int j = i + 1; j <= n; j++)
		{
			int p = current[i][1] > current[j][1] ? current[i][1] - current[j][1] : current[j][1] - current[i][1];
			if (p == 0) return INT_MIN;
			if (p == 1) value -= 5;
		}
	}
	return value;
}



void ClearValue()//每一课程排课前，清空
{
	bestval = INT_MIN;
	for (int i = 0; i < 4; i++)
	{
		best[i][0] = -1;
		best[i][1] = -1;
		best[i][2] = -1;
	}
}



void Dfs(int len, int depth)
{
	if (len == 0)
	{
		currentval = Value(depth - 1);
		if (currentval >= bestval)
		{
			bestval = currentval;
			for (int i = 0; i < depth; i++)
			{
				best[i][0] = current[i][0];
				best[i][1] = current[i][1];
				best[i][2] = current[i][2];
			}
			for (int i = depth; i < 4; i++)
			{
				best[i][0] = -1;
				best[i][1] = -1;
				best[i][2] = -1;
			}
		}
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (!ifcourse[i][j])
			{
				ifcourse[i][j] = 1;
				int length = (i == 0 || i == 2 ? 2 : 3);
				if (len < length)
				{
					ifcourse[i][j] = 0;
					continue;
				}
				current[depth][0] = i;
				current[depth][1] = j;
				Dfs(len - length, depth + 1);
				ifcourse[i][j] = 0;
			}
		}
	}
}

void GetBestArrange(Course& course)
{
	Dfs(course.period, 0);
}

bool ArrangeCourse(Course& course, int cterm)
{
	int len = course.period, term = course.term;
	string name = course.name;

	if (term != cterm && term != 0) return false;

	GetBestArrange(course);

	if (bestval != INT_MIN)
	{
		for (int i = 0; i < 4; i++) {
			if (best[i][0] >= 0)
			{
				ifcourse[best[i][0]][best[i][1]] = 1;
				Table[best[i][0]][best[i][1]] = course.name;
			}
		}
		return true;
	}
	return false;
}

bool ArrangeTerm(int& num, int term)
{
	Course* del = new Course[num];
	int i = 0, kk = 0;
	int* p = Courses.Count(), n = Courses.size();

	for (int j = 0; j < n; j++)
	{
		if (*p == 0 && Courses.list()->data[kk].term == term)
		{
			ClearValue();
			bool read = ArrangeCourse(Courses.list()->data[kk], term);
			if (read)
			{
				del[i++] = Courses.list()->data[kk];
			}
		}
		kk++;
		p++;
	}

	kk = 0;
	p = Courses.Count();
	for (int j = 0; j < n; j++)
	{
		if (*p == 0 && (i < coursenum[term - 1] && Courses.list()->data[kk].term == 0))
		{
			ClearValue();
			bool read = ArrangeCourse(Courses.list()->data[kk], term);
			if (read)
			{
				del[i++] = Courses.list()->data[kk];
			}
		}
		kk++;
		p++;
	}
	for (int j = 0; j < i; j++)
	{
		Courses.DeleteVertice(del[j]);
		num--;
	}

	delete[]del;
	if (i != coursenum[term - 1]) return false;
	return true;
}

void PrintClass(ofstream& out, int term)
{
	out << "第" << term << "学期：\n";
	out << setw(32) << setiosflags(ios::left) << setfill(' ') << " " << "\t"
		<< setw(32) << setiosflags(ios::left) << setfill(' ') << "周一" << "\t"
		<< setw(32) << setiosflags(ios::left) << setfill(' ') << "周二" << "\t"
		<< setw(32) << setiosflags(ios::left) << setfill(' ') << "周三" << "\t"
		<< setw(32) << setiosflags(ios::left) << setfill(' ') << "周四" << "\t"
		<< setw(32) << setiosflags(ios::left) << setfill(' ') << "周五" << "\t"
		<< endl;
	out << endl;
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:out << setw(32) << setiosflags(ios::left) << setfill(' ') << "第1-2节" << "\t" << "|"; break;
		case 1:out << setw(32) << setiosflags(ios::left) << setfill(' ') << "第3-5节" << "\t" << "|"; break;
		case 2:out << setw(32) << setiosflags(ios::left) << setfill(' ') << "第6-7节" << "\t" << "|"; break;
		case 3:out << setw(32) << setiosflags(ios::left) << setfill(' ') << "第8-10节" << "\t" << "|"; break;
		}
		for (int j = 0; j < 5; j++)
		{
			if (ifcourse[i][j]) out << setw(32) << setiosflags(ios::left) << setfill(' ') << Table[i][j].c_str() << "\t" << "|";
			else out << setw(32) << setiosflags(ios::left) << setfill(' ') << " " << "\t" << "|";
		}
		out << "\n\n";
	}
	out << "\n";
}


int main()
{
	ifstream infile("9_1953871_邓泉.txt");
	ofstream outfile("out.txt");

	int classnumber = 0;//初始化课程数
	bool read = GetData(infile, classnumber);//文件读入
	if (!read)//error
	{
		outfile << "开设课程数与课程总数不相等" << endl;
		cout << "开设课程数与课程总数不相等" << endl;
		system("pause");
		return 0;
	}

	int term = 1;//学期
	while (classnumber > 0)
	{
		TableClear();
		read = ArrangeTerm(classnumber, term);//安排当前学期课表
		if (!read)//error
		{
			outfile << "无法匹配，程序中止" << endl;
			cout << "无法匹配，程序中止" << endl;
			system("pause");
			return 0;
		}
		PrintClass(outfile, term);//打印课表
		//PrintTable(term);
		term++;//下一学期
	}

	cout << "课表已生成" << endl;
	system("pause");
	return 0;
}