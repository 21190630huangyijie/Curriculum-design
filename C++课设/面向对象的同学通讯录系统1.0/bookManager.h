#pragma once
#include<iostream>
#include<fstream>
#include"address.h"
#include"student.h"
using namespace std;

class BookManager    //通讯录管理类
{
public:

	BookManager();   //构造函数

	void show_Menu();  //展示菜单

	void Add_Stu();   //添加学生信息

	void Save();     //将信息保存进文件

	void Exit_System();  //退出系统

	int number;    //记录人数

	bool Is_empty;   //判读文件是否为空

	void init_Stu();   //将文件信息输出

	void show_Stu();   //展示信息

	void del_Stu();    //删除学生信息

	void mod_Stu();   //修改学生信息

	void find_Stu();  //查找学生信息

	int Is_Exist(string name);  //判断某人是否存在

	int get_number();   //获取文件中人数

	Student** m_StuArray;  //学生数组指针

	~BookManager();    //析构函数
	
};


