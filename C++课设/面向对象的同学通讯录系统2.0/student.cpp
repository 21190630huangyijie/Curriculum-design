#include"student.h"

Student::Student(string Name, string College, string Class, string Tel, string Phone,
	string Email, string Address, string Post)   //构造函数
{
	m_Name = Name;
	m_College = College;
	m_Class = Class;
	m_Tel = Tel;
	m_Phone = Phone;
	m_Email = Email;
	m_Address = Address;
	m_Post = Post;
}
//显示通讯信息
void Student::showAddress()
{
	cout << "  手机：" << m_Tel
		<< "  家庭电话：" << m_Phone
		<< "  电子邮箱：" << m_Email
		<< "  家庭地址：" << m_Address
		<< "  邮编：" << m_Post << endl;
}
//显示学生信息
void Student::showStudent()
{
	cout << "姓名：" << m_Name<< "  院系：" << m_College<< "  班级：" << m_Class;
}
Student::~Student()
{
}