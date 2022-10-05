#pragma once
#include<iostream>
#include<string>
using namespace std;

//创建通讯录抽象类
class Address
{
public:
	string m_Tel;   //手机号
	string m_Phone;  //家庭电话
	string m_Email;   //电子邮件
	string m_Address;  //家庭地址
	string m_Post;    //邮编

	//显示通讯信息
	virtual void showAddress() = 0;    //抽象类
	//显示学生信息
	virtual void showStudent() = 0;    //抽象类

};

