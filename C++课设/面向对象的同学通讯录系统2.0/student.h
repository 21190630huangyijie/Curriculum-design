#pragma once
#include<iostream>
#include"address.h"
using namespace std;

//����ѧ����
class Student :public Address   //�̳�ͨѶ¼��
{
public:
	Student(string Name, string College, string Class, string Tel,string Phone,
		string Email, string Address, string Post );   //���캯��
	//��ʾͨѶ��Ϣ
	//virtual void showAddress() ;    //������
	//��ʾѧ����Ϣ
	//virtual void showStudent() ;    //������
	void showAddress();
	void showStudent();

	string m_Name;     //����
	string m_College;   //Ժϵ
	string m_Class;    //�༶
	~Student();
};