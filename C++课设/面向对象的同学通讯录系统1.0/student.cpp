#include"student.h"

Student::Student(string Name, string College, string Class, string Tel, string Phone,
	string Email, string Address, string Post)   //���캯��
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
//��ʾͨѶ��Ϣ
void Student::showAddress()
{
	cout << "  �ֻ���" << m_Tel
		<< "  ��ͥ�绰��" << m_Phone
		<< "  �������䣺" << m_Email
		<< "  ��ͥ��ַ��" << m_Address
		<< "  �ʱࣺ" << m_Post << endl;
}
//��ʾѧ����Ϣ
void Student::showStudent()
{
	cout << "������" << m_Name<< "  Ժϵ��" << m_College<< "  �༶��" << m_Class;
}
Student::~Student()
{
}