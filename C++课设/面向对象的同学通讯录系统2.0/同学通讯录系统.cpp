#include<iostream>
#include"bookManager.h"
#include"address.h"
#include"student.h"
using namespace std;

int main()
{
	BookManager bm;           //ʵ�����������
	int choice = 0;            //�û��Ĺ���ѡ��
	/*
	Address* add = NULL;
	add = new Student("����", "�Ƶ�Ժ", "192001", "10086", "110", "192001@qq.com", "�����Ͼ�", "338000");
	add->showStudent();
	add->showAddress();
	*/
	while (true)
	{
		bm.show_Menu();          //���ò˵�
		cout << "�밴�ղ˵�����ʾ�������֣�" << endl;
		cin >> choice;    //��������ʹ�õĹ��������������
		switch (choice)
		{
		case 1:       //�����Ϣ
			bm.Add_Stu();
			break;
		case 2:       //��ʾ��Ϣ
			bm.show_Stu();
			break;
		case 3:       //ɾ����Ϣ
			bm.del_Stu();
			break; 
		case 4:       //�޸���Ϣ
			bm.mod_Stu();
			break;
		case 5:       //��ѯ��Ϣ
			bm.find_Stu();
			break;
		case 6:       //�˳�ϵͳ
			bm.Exit_System();     //�����˳�ϵͳ����
			break;
		default:
			system("cls");    //����������������
			break;
		}
	}



	system("pause");
	return 0;
}