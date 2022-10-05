#pragma once
#include<iostream>
#include"address.h"
using namespace std;

//创建学生类
class Student :public Address   //继承通讯录类
{
public:
	Student(string Name, string College, string Class, string Tel,string Phone,
		string Email, string Address, string Post );   //构造函数
	//显示通讯信息
	//virtual void showAddress() ;    //抽象类
	//显示学生信息
	//virtual void showStudent() ;    //抽象类
	void showAddress();
	void showStudent();

	string m_Name;     //姓名
	string m_College;   //院系
	string m_Class;    //班级
	~Student();
};