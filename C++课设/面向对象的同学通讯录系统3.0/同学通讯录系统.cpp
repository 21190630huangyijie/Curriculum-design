#include<iostream>
#include"bookManager.h"
#include"address.h"
#include"student.h"
using namespace std;

int main()
{
	BookManager bm;           //实例化管理对象
	int choice = 0;            //用户的功能选择

	while (true)
	{
		bm.show_Menu();          //调用菜单
		cout << "请按照菜单上提示输入数字：" << endl;
		cin >> choice;    //输入你想使用的功能所代表的数字
		switch (choice)
		{
		case 1:       //添加信息
			bm.Add_Stu();
			break;
		case 2:       //显示信息
			bm.show_Stu();
			break;
		case 3:       //删除信息
			bm.del_Stu();
			break; 
		case 4:       //修改信息
			bm.mod_Stu();
			break;
		case 5:       //查询信息
			bm.find_Stu();
			break;
		case 6:       //退出系统
			bm.Exit_System();     //调用退出系统函数
			break;
		default:
			system("cls");    //输入其他数字清屏
			break;
		}
	}



	system("pause");
	return 0;
}