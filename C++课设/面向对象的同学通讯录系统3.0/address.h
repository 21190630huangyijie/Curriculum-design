#pragma once
#include<iostream>
#include<string>
using namespace std;

//����ͨѶ¼������
class Address
{
public:
	string m_Tel;   //�ֻ���
	string m_Phone;  //��ͥ�绰
	string m_Email;   //�����ʼ�
	string m_Address;  //��ͥ��ַ
	string m_Post;    //�ʱ�

	//��ʾͨѶ��Ϣ
	virtual void showAddress() = 0;    //������
	//��ʾѧ����Ϣ
	virtual void showStudent() = 0;    //������

};

