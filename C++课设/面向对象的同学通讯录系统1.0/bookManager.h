#pragma once
#include<iostream>
#include<fstream>
#include"address.h"
#include"student.h"
using namespace std;

class BookManager    //ͨѶ¼������
{
public:

	BookManager();   //���캯��

	void show_Menu();  //չʾ�˵�

	void Add_Stu();   //���ѧ����Ϣ

	void Save();     //����Ϣ������ļ�

	void Exit_System();  //�˳�ϵͳ

	int number;    //��¼����

	bool Is_empty;   //�ж��ļ��Ƿ�Ϊ��

	void init_Stu();   //���ļ���Ϣ���

	void show_Stu();   //չʾ��Ϣ

	void del_Stu();    //ɾ��ѧ����Ϣ

	void mod_Stu();   //�޸�ѧ����Ϣ

	void find_Stu();  //����ѧ����Ϣ

	int Is_Exist(string name);  //�ж�ĳ���Ƿ����

	int get_number();   //��ȡ�ļ�������

	Student** m_StuArray;  //ѧ������ָ��

	~BookManager();    //��������
	
};


