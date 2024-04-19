#include<iostream>
#include<fstream>
#include<sstream>
#include<Windows.h>
#include<iomanip>
#include<limits.h>
#include<io.h>
using namespace std;

#define MAX_SIZE 50

#define MaxTerm 10//ÿѧ�����γ���


class Edge
{
public:
	Edge() { head = tail = value = 0; };
	Edge(int h, int t, int v) :head(h), tail(t), value(v) {};//���ι��캯��
	bool operator<(const Edge& p) { return this->value < p.value; }
	bool operator>(const Edge& p) { return this->value > p.value; }
	int head;//���
	int tail;//�յ�
	int value;//�ߵ�Ȩֵ
};


struct Course
{
	Course() :period(0), term(0) {};
	Course(string pnum, string pname, int p, int t) :num(pnum), name(pname), period(p), term(t) {};
	bool operator==(const Course& pcourse) { return this->num == pcourse.num; }
	string operator=(const Course& pcourse) { num = pcourse.num; name = pcourse.name; period = pcourse.period; term = pcourse.term; return name; }
	string num;//�γ̱��
	string name;//�γ�����
	int period;//ѧʱ
	int term;//ָ������ѧ�ڣ���Ϊ0������Զ��ſ�
};

class ClassList
{
private:
	int maxsize;//��������С
	int size;//��ǰ�����С

public:
	Course* data;//������ݵ�����
	ClassList() :maxsize(MAX_SIZE), size(0) { data = new Course[maxsize + 1]; }//���캯��
	~ClassList() { delete[] data; }//��������
	void insert(Course& t)//����Ԫ��
	{
		data[size] = t;
		size++;
	}
	void remove(Course& t)//ɾ��Ԫ��
	{
		int i = find(t);
		for (int j = i; j < size - 1; j++)
		{
			data[j] = data[j + 1];
		}
		size--;
	}
	int find(Course& t)//���Ҹ�Ԫ�ش���������λ��
	{
		for (int i = 0; i < size; i++)
		{
			if (data[i] == t) return i;
		}
		return -1;
	}
};

//ͼ����ʵ��


class Graph
{
private:
	int maxsize;//�����������
	int verticenum;//��ǰ�Ķ�����
	int edgenum;//��ǰ�ı���
	int** edge;//�ڽӾ���
	ClassList* List;//��Ŷ�����б�
	int* count;//��ʾ����������
public:
	Graph() :maxsize(MAX_SIZE), verticenum(0), edgenum(0)//���캯��
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
	~Graph()//��������
	{
		delete List;
		for (int i = 0; i < maxsize; i++) delete[] edge[i];
		delete[] edge;
		delete[] count;
	}
	void AddEdge(Course h, Course t, int v = 1);//��ӱ�
	void AddVertice(Course node);//��Ӷ���
	void DeleteVertice(Course node);//ɾ������
	int EdgeNum() const { return edgenum; }//���رߵĸ���
	int size() const { return verticenum; }//���ض���ĸ���
	ClassList* list() const { return List; }//���ض����б�
	int* Count() const { return count; }//����count����ָ��

};

void Graph::AddEdge(Course  h, Course t, int v)
{
	if (v < 0)
	{
		cout << "�ߵ�Ȩֵ���Ϸ���������" << endl;
		return;
	}//Ȩֵ����������

	int i = List->find(h), j = List->find(t);
	if (i >= 0 && j >= 0)
	{
		edge[i][j] = v;
	}
	else
	{
		cout << "δ���ҵ��ߵĶ��㣬��ӱ�ʧ�ܣ�������" << endl;
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
	}//���д�i��j������ߣ���j����ȼ�һ

	for (int j = i; j < size() - 1; j++) {
		for (int k = 0; k < size(); k++) {
			edge[j][k] = edge[j + 1][k];
			edge[k][j] = edge[k][j + 1];
		}
	}//���ڽӾ���ƽ��

	for (int j = i; j < size() - 1; j++)
	{
		count[j] = count[j + 1];
	}//count����ƽ��

	verticenum--;
	List->remove(node);
}



Graph Courses;//�������пγ̵�ͼ

int coursenum[MaxTerm];//ÿѧ��ָ���Ŀγ���

inline int StrToInt(string& str)//string��int��ת��
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

Course* GetFromNum(const string& num)//���ݿγ̵ı���������пγ�
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



bool GetData(ifstream& infile, int& num)//���ļ��������ݣ�������ͼ��
{
	if (!infile.is_open())
	{
		cerr << "�޷����ļ�" << endl;
		return false;
	}

	int k = 0, count = 0;
	while (infile >> coursenum[k])//����ÿѧ���ϵĿγ���
	{
		count += coursenum[k];
		k++;
		if (infile.get() == '\n') break;
	}

	string data[10];
	int i = 0;
	while (infile >> data[i++])
	{
		if (infile.get() == '\n')//����ǰ�����������
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


//Ȩֵ����
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



void ClearValue()//ÿһ�γ��ſ�ǰ�����
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
	out << "��" << term << "ѧ�ڣ�\n";
	out << setw(32) << setiosflags(ios::left) << setfill(' ') << " " << "\t"
		<< setw(32) << setiosflags(ios::left) << setfill(' ') << "��һ" << "\t"
		<< setw(32) << setiosflags(ios::left) << setfill(' ') << "�ܶ�" << "\t"
		<< setw(32) << setiosflags(ios::left) << setfill(' ') << "����" << "\t"
		<< setw(32) << setiosflags(ios::left) << setfill(' ') << "����" << "\t"
		<< setw(32) << setiosflags(ios::left) << setfill(' ') << "����" << "\t"
		<< endl;
	out << endl;
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:out << setw(32) << setiosflags(ios::left) << setfill(' ') << "��1-2��" << "\t" << "|"; break;
		case 1:out << setw(32) << setiosflags(ios::left) << setfill(' ') << "��3-5��" << "\t" << "|"; break;
		case 2:out << setw(32) << setiosflags(ios::left) << setfill(' ') << "��6-7��" << "\t" << "|"; break;
		case 3:out << setw(32) << setiosflags(ios::left) << setfill(' ') << "��8-10��" << "\t" << "|"; break;
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
	ifstream infile("9_1953871_��Ȫ.txt");
	ofstream outfile("out.txt");

	int classnumber = 0;//��ʼ���γ���
	bool read = GetData(infile, classnumber);//�ļ�����
	if (!read)//error
	{
		outfile << "����γ�����γ����������" << endl;
		cout << "����γ�����γ����������" << endl;
		system("pause");
		return 0;
	}

	int term = 1;//ѧ��
	while (classnumber > 0)
	{
		TableClear();
		read = ArrangeTerm(classnumber, term);//���ŵ�ǰѧ�ڿα�
		if (!read)//error
		{
			outfile << "�޷�ƥ�䣬������ֹ" << endl;
			cout << "�޷�ƥ�䣬������ֹ" << endl;
			system("pause");
			return 0;
		}
		PrintClass(outfile, term);//��ӡ�α�
		//PrintTable(term);
		term++;//��һѧ��
	}

	cout << "�α�������" << endl;
	system("pause");
	return 0;
}