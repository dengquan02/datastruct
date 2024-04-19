#pragma once
#include <iostream>
using namespace std;



template <class T>
struct TreeNode
{
    //构造函数
    TreeNode(const T& value, TreeNode<T>* next = NULL, TreeNode<T>* link = NULL) : value(value), next(next), link(link) {}
    TreeNode(TreeNode<T>* next = NULL, TreeNode<T>* link = NULL) : next(next), link(link) {}

    T value;
    TreeNode<T>* next;                          //指向子女结点头结点的指针
    TreeNode<T>* link;                          //指向兄弟结点的指针
};


template<class T>
class Tree
{
public:

    //构造函数
    Tree() :root(NULL) {};

    //析构函数
    ~Tree()
    {
        destroy(root);
    }

    //建立祖先结点
    void buildRoot(T& Root)
    {
        root = new TreeNode<T>(Root);
    }

    //插入新结点（添加新成员）
    bool Insert(T& fatherName, T& childName)
    {
        TreeNode<T>* father = Find(fatherName);
        if (father == NULL)                         //插入失败
        {
            //cerr << "插入失败" << endl;
            return false;
        }

        if (father->next == NULL)                             //原本无子女，直接插入
        {
            father->next = new TreeNode<T>(childName);
            if (father->next)
            {
                //cerr << "内存分配错误，插入失败" << endl;
                return false;
            }
        }
        else
        {
            TreeNode<T>* p = father->next;                    //找到要插入的位置
            while (p->link != NULL)
            {
                p = p->link;
            }
            p->link = new TreeNode<T>(childName);
            if (p->link)
            {
                //cerr << "内存分配错误，插入失败" << endl;
                return false;
            }
        }

        return true;
    }


    //删除自身和所有子孙
    void Destroy(T& fatherName)
    {
        TreeNode<T>* father = Find(fatherName);
        if (father == NULL)
        {
            cerr << "查无此人！删除失败！" << endl;
            return;
        }
        TreeNode<T>* p = father->next;
        destroy(p);                     //删除所有子孙
        delete father;                  //删除自己
    }
    //删除自己和所有的兄弟和子孙
    void destroy(TreeNode<T>* subTree)
    {
        if (subTree != NULL)
        {
            destroy(subTree->next);
            destroy(subTree->link);
            delete subTree;
        }
    }

    //更改家庭成员姓名
    bool Update(T& curName, T& newName)
    {
        TreeNode<T>* p = Find(curName);
        if (p == NULL)
        {
            cerr << "查无此人！更改失败！" << endl;
            return false;
        }
        p->value = newName;
        return true;
    }

    //输出第一代子孙
    void Show(T& fatherName)
    {
        TreeNode<T>* father = Find(fatherName);
        if (father == NULL)
        {
            cerr << "查无此人！无法输出！" << endl;
            return;
        }

        TreeNode<T>* p = father->next;
        if (p == NULL)
        {
            cerr << "当前结点没有子孙！" << endl;
            return;
        }

        while (p != NULL)
        {
            cout << p->value << " ";
            p = p->link;
        }
        cout << endl;
    }

    //寻找姓名为name的结点
    TreeNode<T>* Find(T& name)
    {
        return Find(root, name);
    }


private:
    //以subTree为起点寻找姓名为name的结点，若找到则返回此结点的位置
    TreeNode<T>* Find(TreeNode<T>* subTree, T& name)
    {
        if (subTree == NULL)                                     //未找到，无法继续往下找
        {
            return NULL;
        }
        if (subTree->value == name)                              //找到，返回此结点的位置
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

