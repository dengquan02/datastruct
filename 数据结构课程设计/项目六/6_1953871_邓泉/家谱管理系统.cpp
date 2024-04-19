#include<iostream>
#include <string>
#include "Tree.hpp"
using namespace std;


int main()
{
    //打印菜单界面
    cout << "**            家谱管理系统             **" << endl;
    cout << "=========================================" << endl;
    cout << "**          请选择要执行的操作         **" << endl;
    cout << "**            A---完善家谱             **" << endl;
    cout << "**            B---添加家庭成员         **" << endl;
    cout << "**            C---解散局部家庭         **" << endl;
    cout << "**            D---更改家庭成员姓名     **" << endl;
    cout << "**            E---查询家谱             **" << endl;
    cout << "**            F---退出程序             **" << endl;
    cout << "=========================================" << endl;

    //建立新家谱
    Tree<string> Family;
    string RootName;
    cout << "首先建立一个家谱!" << endl;
    cout << "请输入祖先的姓名：";
    cin >> RootName;
    Family.buildRoot(RootName);
    cout << "此家谱的祖先是：" << RootName << endl;


    //执行操作
    char choice;
    bool isContinue = true;
    while (isContinue)
    {
        cout << "\n请选择要执行的操作:";
        cin >> choice;
        switch (choice)
        {
        case 'A':
        {
            cout << "请输入要建立家庭的人的姓名:";
            string fatherName;
            cin >> fatherName;
            cout << "请输入" << fatherName << "的儿女人数：";
            int childCount;
            cin >> childCount;
            if (childCount < 0)
            {
                cerr << "儿女人数不能为负数！" << endl;
                break;
            }
            cout << "请依次输入" << fatherName << "的儿女的姓名：";
            string childName;
            if (Family.Find(fatherName))
            {
                while (childCount--)
                {
                    cin >> childName;
                    Family.Insert(fatherName, childName);
                }
            }
            else
            {
                cerr << "\n查无此人，添加失败！" << endl;
                break;
            }
            cout << fatherName << "的第一代子孙是：";
            Family.Show(fatherName);
            break;
        }
        case 'B':
        {
            cout << "请输入要添加儿子（或女儿）的人的姓名:";
            string fatherName;
            cin >> fatherName;
            if (Family.Find(fatherName))
            {
                cout << " 请输入" << fatherName << "新添加的儿子（或女儿）的姓名：";
                string childName;
                cin >> childName;
                Family.Insert(fatherName, childName);
            }
            else
            {
                cerr << "\n查无此人，添加失败！" << endl;
                break;
            }
            cout << fatherName << "的第一代子孙是：";
            Family.Show(fatherName);
            break;
        }
        case 'C':
        {
            cout << "请输入要解散家庭的人的姓名：";
            string fatherName;
            cin >> fatherName;
            //删除操作
            cout << "要解散家庭的人是" << fatherName << endl;
            cout << fatherName << "的第一代子孙是:";
            Family.Show(fatherName);
            Family.Destroy(fatherName);
            break;
        }
        case 'D':
        {
            cout << "请输入更改姓名的人的目前姓名：";
            string curName;
            cin >> curName;
            cout << "请输入更改后的姓名：";
            string newName;
            cin >> newName;

            if (Family.Update(curName, newName) != NULL)
            {
                cout << curName << "已更名为" << newName << endl;
            }
            break;
        }
        case 'E':
        {
            cout << " 请输入要查询人的姓名：";
            string curName;
            cin >> curName;
            Family.Show(curName);
            break;
        }
        case 'F':
        {
            isContinue = false;
            break;
        }
        default:cerr << "您所选择的操作不合法！" << endl;
        }
    }

    system("pause");
    return 0;
}
