#pragma once
#include <iostream>
using namespace std;



template <class T>
struct TreeNode
{
    //���캯��
    TreeNode(const T& value, TreeNode<T>* next = NULL, TreeNode<T>* link = NULL) : value(value), next(next), link(link) {}
    TreeNode(TreeNode<T>* next = NULL, TreeNode<T>* link = NULL) : next(next), link(link) {}

    T value;
    TreeNode<T>* next;                          //ָ����Ů���ͷ����ָ��
    TreeNode<T>* link;                          //ָ���ֵܽ���ָ��
};


template<class T>
class Tree
{
public:

    //���캯��
    Tree() :root(NULL) {};

    //��������
    ~Tree()
    {
        destroy(root);
    }

    //�������Ƚ��
    void buildRoot(T& Root)
    {
        root = new TreeNode<T>(Root);
    }

    //�����½�㣨����³�Ա��
    bool Insert(T& fatherName, T& childName)
    {
        TreeNode<T>* father = Find(fatherName);
        if (father == NULL)                         //����ʧ��
        {
            //cerr << "����ʧ��" << endl;
            return false;
        }

        if (father->next == NULL)                             //ԭ������Ů��ֱ�Ӳ���
        {
            father->next = new TreeNode<T>(childName);
            if (father->next)
            {
                //cerr << "�ڴ������󣬲���ʧ��" << endl;
                return false;
            }
        }
        else
        {
            TreeNode<T>* p = father->next;                    //�ҵ�Ҫ�����λ��
            while (p->link != NULL)
            {
                p = p->link;
            }
            p->link = new TreeNode<T>(childName);
            if (p->link)
            {
                //cerr << "�ڴ������󣬲���ʧ��" << endl;
                return false;
            }
        }

        return true;
    }


    //ɾ���������������
    void Destroy(T& fatherName)
    {
        TreeNode<T>* father = Find(fatherName);
        if (father == NULL)
        {
            cerr << "���޴��ˣ�ɾ��ʧ�ܣ�" << endl;
            return;
        }
        TreeNode<T>* p = father->next;
        destroy(p);                     //ɾ����������
        delete father;                  //ɾ���Լ�
    }
    //ɾ���Լ������е��ֵܺ�����
    void destroy(TreeNode<T>* subTree)
    {
        if (subTree != NULL)
        {
            destroy(subTree->next);
            destroy(subTree->link);
            delete subTree;
        }
    }

    //���ļ�ͥ��Ա����
    bool Update(T& curName, T& newName)
    {
        TreeNode<T>* p = Find(curName);
        if (p == NULL)
        {
            cerr << "���޴��ˣ�����ʧ�ܣ�" << endl;
            return false;
        }
        p->value = newName;
        return true;
    }

    //�����һ������
    void Show(T& fatherName)
    {
        TreeNode<T>* father = Find(fatherName);
        if (father == NULL)
        {
            cerr << "���޴��ˣ��޷������" << endl;
            return;
        }

        TreeNode<T>* p = father->next;
        if (p == NULL)
        {
            cerr << "��ǰ���û�����" << endl;
            return;
        }

        while (p != NULL)
        {
            cout << p->value << " ";
            p = p->link;
        }
        cout << endl;
    }

    //Ѱ������Ϊname�Ľ��
    TreeNode<T>* Find(T& name)
    {
        return Find(root, name);
    }


private:
    //��subTreeΪ���Ѱ������Ϊname�Ľ�㣬���ҵ��򷵻ش˽���λ��
    TreeNode<T>* Find(TreeNode<T>* subTree, T& name)
    {
        if (subTree == NULL)                                     //δ�ҵ����޷�����������
        {
            return NULL;
        }
        if (subTree->value == name)                              //�ҵ������ش˽���λ��
        {
            return subTree;
        }
        if (Find(subTree->link, name) != NULL)
        {
            return Find(subTree->link, name);
        }
        return Find(subTree->next, name);
    }

    TreeNode<T>* root;
};

