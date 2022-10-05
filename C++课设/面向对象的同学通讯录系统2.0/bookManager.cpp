#include"bookManager.h"
#include"address.h"
#include"student.h"
#define Filename addresslist.txt    //用宏定义，方便修改文件名
BookManager::BookManager()    //构造函数
{
	//初始化文件
	ifstream fp;
	fp.open("Filename",ios::in);
	if (!fp.is_open())    //当文件不存在
	{
		//cout << "文件不存在" << endl;
		this->number = 0;   //初始化人数为0
		this->m_StuArray = NULL;
		this->Is_empty = true;
		fp.close();
		return;  //返回
	}
	char ch;
	fp >> ch;
	if (fp.eof())   //当文件为空
	{
		//cout << "文件为空！" << endl;
		this->number = 0;   //初始化人数为0
		this->m_StuArray = NULL;
		this->Is_empty = true;
		fp.close();
		return;   //返回
	}

	int sum = this->get_number();
	//cout << "学生人数是：" << sum << "人" << endl;
	this->number = sum;

	this->m_StuArray = new Student * [sum];
	this->init_Stu();  //将文件的数据输出
	/*
	for (int i = 0; i < this->number; i++)   //将数据写入文件
	{
		cout << this->m_StuArray[i]->m_Name << " "
			<< this->m_StuArray[i]->m_College << " "
			<< this->m_StuArray[i]->m_Class << " "
			<< this->m_StuArray[i]->m_Tel << " "
			<< this->m_StuArray[i]->m_Phone << " "
			<< this->m_StuArray[i]->m_Email << " "
			<< this->m_StuArray[i]->m_Address << " "
			<< this->m_StuArray[i]->m_Post << " " << endl;
	}
	*/
}
int BookManager::get_number()
{
	ifstream fp;
	fp.open("Filename", ios::in);  //读文件
	string Name, College, Class, Tel, Phone,
		Email, address, Post;
	int num = 0;
	while (fp >> Name && fp >> College && fp >> Class && fp >> Tel && fp >> Phone &&
		fp >> Email && fp >> address && fp >> Post)    //数据输出
	{
		num++;
	}
	return num;
}

void BookManager::init_Stu()   //将原来的数据初始化
{
	ifstream fp;
	fp.open("Filename", ios::in);  //读文件
	string Name, College, Class, Tel, Phone,
		Email, address, Post;
	int i = 0;
	while (fp >> Name && fp >> College && fp >> Class && fp >> Tel && fp >> Phone &&
		fp >> Email && fp >> address && fp >> Post)
	{
		Student* stu = NULL;
		stu = new Student(Name, College, Class, Tel, Phone,
			Email, address, Post);
		this->m_StuArray[i] = stu;
		i++;
	}
	fp.close();
}
void BookManager::show_Menu()           //展示菜单
{
	cout << "*************************************" << endl;
	cout << "****** 欢迎使用同学通讯录系统！******" << endl;
	cout << "********* 1.添加同学信息  ***********" << endl;
	cout << "********* 2.显示同学信息  ***********" << endl;
	cout << "********* 3.删除同学信息  ***********" << endl;
	cout << "********* 4.修改同学信息  ***********" << endl;
	cout << "********* 5.查询同学信息  ***********" << endl;
	cout << "********* 6.退出通讯系统  ***********" << endl;   
	cout << "*************************************" << endl;
	cout << endl;
}

void BookManager::Add_Stu()
{
	cout << "请输入添加的学生数：" << endl;
	int sum = 0;
	cin >> sum;
	if (sum > 0)
	{
		int newNum = sum + number;    //计算加入后的人数
		Student** newSpace = new Student * [newNum];  //开辟新的空间
		if (this->m_StuArray != NULL)
		{
			for (int i = 0; i < this->number; i++)
			{
				newSpace[i] = this->m_StuArray[i];
			}
		}
		//添加新数据
		for (int i = 0; i < sum; i++)
		{
			string Name, College, Class, Tel, Phone,
				Email, address, Post;    //定义相关数据
			cout << "请按顺序输入第" << i + 1
				<< "个同学的姓名、院系、班级、手机、家庭电话、电子邮件、家庭地址、邮编：" << endl;
			cin >> Name >> College >> Class >> Tel >> Phone >> Email >> address >> Post;  //输入相关数据

			Student* add = NULL;
			add = new Student(Name, College, Class, Tel, Phone, Email, address, Post);
			newSpace[this->number + i] = add;   //在原有的基础上继续添加

		}
		this->Is_empty = false;      //文件不为空
		this->m_StuArray = newSpace;
		this->number = newNum;         //更新学生人数
		cout << "添加成功！" << endl;
		this->Save();      //将数据导入文件
	}
	else
	{
		cout << "输入有误！" << endl;
	}
	//按任意键清屏回到上级目录
	system("pause");
	system("cls");
}
void BookManager::show_Stu()
{
	if (this->Is_empty)
		cout << "文件为空或不存在！" << endl;
	else
	{
		for (int i = 0; i < number; i++)
		{
			this->m_StuArray[i]->showStudent();
			this->m_StuArray[i]->showAddress();
		}
	}
	system("pause");
	system("cls");
}
int BookManager::Is_Exist(string name)
{
	int flag = -1;

	for (int i = 0; i < this->number; i++)
	{
		if (this->m_StuArray[i]->m_Name == name)
		{
			flag = i;
			break;
		}
	}
	return flag;
}
void BookManager::del_Stu()
{
	if (this->Is_empty) cout << "文件不存在或为空！" << endl;
	else
	{
		cout << "请输入你想删除的名字：" << endl;
		string name;
		cin >> name;
		int flag = this->Is_Exist(name);
		if (flag!=-1 )   //如果该同学存在
		{
			for (int i = flag; i < this->number - 1; i++)
			{
				this->m_StuArray[i] = this->m_StuArray[i + 1];  //将此数据后的数据前移
			}
			this->number--;        //更新人数
			this->Save();        //将删除后的信息更新到文件中
			cout << "删除成功！" << endl;
			system("pause");
			system("cls");
		}
		else cout << "未找到该同学！" << endl;
	}
}
void BookManager::mod_Stu()
{
	if (this->Is_empty)   //文件为空
	{
		cout << "文件不存在或为空！" << endl;
	}
	else
	{
		cout << "请输入要修改的同学姓名：" << endl;
		string name;
		cin >> name;
		int flag = this->Is_Exist(name);
		if (flag != -1)          //找到要修改的人
		{
			delete this->m_StuArray[flag];    //将要修改的人先删除
			string College, Class, Tel, Phone,
				Email, address, Post;    //定义相关数据
			cout << "请按顺序输入" << name
				<< "同学的新的院系、班级、手机、家庭电话、电子邮件、家庭地址、邮编：" << endl;
			cin >> College >> Class >> Tel >> Phone >> Email >> address >> Post;  //输入相关数据

			Student* stu = NULL;
			stu = new Student(name, College, Class, Tel, Phone,
				Email, address, Post);
			this->m_StuArray[flag] = stu;
			cout << "修改成功！" << endl;
			this->Save();      //保存到文件中
		}
		else cout << "未找到此人！" << endl;
	}
	system("pause");
	system("cls");
}
void BookManager::find_Stu()
{
	if (this->Is_empty)   //文件为空
	{
		cout << "文件不存在或为空！" << endl;
	}
	else
	{
		cout << "请选择查找方式：" << endl;
		cout << "1.按照姓名查询" << endl;
		cout << "2.按照姓名和学院查询" << endl;
		int choice = 0;
		cin >> choice;
		if (choice == 1)     //单一字段查询
		{
			string name;
			int flag = 0;
			cout << "请输入要查询的姓名：" << endl;
			cin >> name;
			for (int i = 0; i < number; i++)
			{
				if (this->m_StuArray[i]->m_Name == name)
				{
					cout << "查找成功，" << name << "的信息如下：" << endl;
					this->m_StuArray[i]->showStudent();
					this->m_StuArray[i]->showAddress();
					flag = 1;
					break;
				}
			}
			if (flag == 0)
				cout << "未查询到此人的信息！" << endl;
		}
		else if (choice == 2)    //多字段联合查询
		{
			string name,college;
			int flag = 0;
			cout << "请输入要查询的姓名和院系：" << endl;
			cin >> name>>college;
			for (int i = 0; i < number; i++)
			{
				if (this->m_StuArray[i]->m_Name == name&&this->m_StuArray[i]->m_College==college)
				{
					cout << "查找成功，" << name << "的信息如下：" << endl;
					this->m_StuArray[i]->showStudent();
					this->m_StuArray[i]->showAddress();
					flag = 1;
					break;
				}
			}
			if (flag == 0)
				cout << "未查询到此人的信息！" << endl;
		}
		else cout << "输入有误！" << endl;
	}
	system("pause");
	system("cls");
}
void BookManager::Save()
{
	ofstream out;
	out.open("Filename", ios::out);   //用输出方式打开文件
	for (int i = 0; i < this->number; i++)   //将数据写入文件
	{
		out << this->m_StuArray[i]->m_Name << " "
			<< this->m_StuArray[i]->m_College << " "
			<< this->m_StuArray[i]->m_Class << " "
			<< this->m_StuArray[i]->m_Tel << " "
			<< this->m_StuArray[i]->m_Phone << " "
			<< this->m_StuArray[i]->m_Email << " "
			<< this->m_StuArray[i]->m_Address << " "
			<< this->m_StuArray[i]->m_Post << " " << endl;
	}
	out.close();
}
void BookManager::Exit_System()  //退出系统
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

BookManager::~BookManager()   //析构函数
{
	
}