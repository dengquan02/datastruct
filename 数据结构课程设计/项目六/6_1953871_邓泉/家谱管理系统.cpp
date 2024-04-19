#include<iostream>
#include <string>
#include "Tree.hpp"
using namespace std;


int main()
{
    //��ӡ�˵�����
    cout << "**            ���׹���ϵͳ             **" << endl;
    cout << "=========================================" << endl;
    cout << "**          ��ѡ��Ҫִ�еĲ���         **" << endl;
    cout << "**            A---���Ƽ���             **" << endl;
    cout << "**            B---��Ӽ�ͥ��Ա         **" << endl;
    cout << "**            C---��ɢ�ֲ���ͥ         **" << endl;
    cout << "**            D---���ļ�ͥ��Ա����     **" << endl;
    cout << "**            E---��ѯ����             **" << endl;
    cout << "**            F---�˳�����             **" << endl;
    cout << "=========================================" << endl;

    //�����¼���
    Tree<string> Family;
    string RootName;
    cout << "���Ƚ���һ������!" << endl;
    cout << "���������ȵ�������";
    cin >> RootName;
    Family.buildRoot(RootName);
    cout << "�˼��׵������ǣ�" << RootName << endl;


    //ִ�в���
    char choice;
    bool isContinue = true;
    while (isContinue)
    {
        cout << "\n��ѡ��Ҫִ�еĲ���:";
        cin >> choice;
        switch (choice)
        {
        case 'A':
        {
            cout << "������Ҫ������ͥ���˵�����:";
            string fatherName;
            cin >> fatherName;
            cout << "������" << fatherName << "�Ķ�Ů������";
            int childCount;
            cin >> childCount;
            if (childCount < 0)
            {
                cerr << "��Ů��������Ϊ������" << endl;
                break;
            }
            cout << "����������" << fatherName << "�Ķ�Ů��������";
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
                cerr << "\n���޴��ˣ����ʧ�ܣ�" << endl;
                break;
            }
            cout << fatherName << "�ĵ�һ�������ǣ�";
            Family.Show(fatherName);
            break;
        }
        case 'B':
        {
            cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�����:";
            string fatherName;
            cin >> fatherName;
            if (Family.Find(fatherName))
            {
                cout << " ������" << fatherName << "����ӵĶ��ӣ���Ů������������";
                string childName;
                cin >> childName;
                Family.Insert(fatherName, childName);
            }
            else
            {
                cerr << "\n���޴��ˣ����ʧ�ܣ�" << endl;
                break;
            }
            cout << fatherName << "�ĵ�һ�������ǣ�";
            Family.Show(fatherName);
            break;
        }
        case 'C':
        {
            cout << "������Ҫ��ɢ��ͥ���˵�������";
            string fatherName;
            cin >> fatherName;
            //ɾ������
            cout << "Ҫ��ɢ��ͥ������" << fatherName << endl;
            cout << fatherName << "�ĵ�һ��������:";
            Family.Show(fatherName);
            Family.Destroy(fatherName);
            break;
        }
        case 'D':
        {
            cout << "����������������˵�Ŀǰ������";
            string curName;
            cin >> curName;
            cout << "��������ĺ��������";
            string newName;
            cin >> newName;

            if (Family.Update(curName, newName) != NULL)
            {
                cout << curName << "�Ѹ���Ϊ" << newName << endl;
            }
            break;
        }
        case 'E':
        {
            cout << " ������Ҫ��ѯ�˵�������";
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
        default:cerr << "����ѡ��Ĳ������Ϸ���" << endl;
        }
    }

    system("pause");
    return 0;
}
