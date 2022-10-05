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

	void showAddress();	//显示通讯信息
	void showStudent(); //显示学生信息

	string m_Name;     //姓名
	string m_College;   //院系
	string m_Class;    //班级
	~Student();
};