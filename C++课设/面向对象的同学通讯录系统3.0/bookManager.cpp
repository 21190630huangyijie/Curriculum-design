#include"bookManager.h"
#include"address.h"
#include"student.h"
//#define Filename "addresslist.txt"    //�ú궨�壬�����޸��ļ���
BookManager::BookManager()    //���캯��
{
	//��ʼ���ļ�
	ifstream fp;
	fp.open(Filename,ios::in);
	if (!fp.is_open())    //���ļ�������
	{
		//cout << "�ļ�������" << endl;
		this->number = 0;   //��ʼ������Ϊ0
		this->m_StuArray = NULL;
		this->Is_empty = true;
		fp.close();
		return;  //����
	}
	char ch;
	fp >> ch;
	if (fp.eof())   //���ļ�Ϊ��
	{
		//cout << "�ļ�Ϊ�գ�" << endl;
		this->number = 0;   //��ʼ������Ϊ0
		this->m_StuArray = NULL;
		this->Is_empty = true;
		fp.close();
		return;   //����
	}

	int sum = this->get_number();
	//cout << "ѧ�������ǣ�" << sum << "��" << endl;
	this->number = sum;

	this->m_StuArray = new Student * [sum];
	this->init_Stu();  //���ļ����������

}
int BookManager::get_number()
{
	ifstream fp;
	fp.open(Filename, ios::in);  //���ļ�
	string Name, College, Class, Tel, Phone,
		Email, address, Post;
	int num = 0;   //��¼����
	while (fp >> Name && fp >> College && fp >> Class && fp >> Tel && fp >> Phone &&
		fp >> Email && fp >> address && fp >> Post)    //�������
	{
		num++;
	}
	return num;
}

void BookManager::init_Stu()   //��ԭ�������ݳ�ʼ��
{
	ifstream fp;
	fp.open(Filename, ios::in);  //���ļ�
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
void BookManager::show_Menu()           //չʾ�˵�
{
	cout << "*************************************" << endl;
	cout << "****** ��ӭʹ��ͬѧͨѶ¼ϵͳ��******" << endl;
	cout << "********* 1.���ͬѧ��Ϣ  ***********" << endl;
	cout << "********* 2.��ʾͬѧ��Ϣ  ***********" << endl;
	cout << "********* 3.ɾ��ͬѧ��Ϣ  ***********" << endl;
	cout << "********* 4.�޸�ͬѧ��Ϣ  ***********" << endl;
	cout << "********* 5.��ѯͬѧ��Ϣ  ***********" << endl;
	cout << "********* 6.�˳�ͨѶϵͳ  ***********" << endl;   
	cout << "*************************************" << endl;
	cout << endl;
}

void BookManager::Add_Stu()    //��ӹ���
{
	cout << "��������ӵ�ѧ������" << endl;
	int sum = 0;
	cin >> sum;
	if (sum > 0)
	{
		int newNum = sum + number;    //�������������
		Student** newSpace = new Student * [newNum];  //�����µĿռ�
		if (this->m_StuArray != NULL)
		{
			for (int i = 0; i < this->number; i++)
			{
				newSpace[i] = this->m_StuArray[i];
			}
		}
		//���������
		for (int i = 0; i < sum; i++)
		{
			string Name, College, Class, Tel, Phone,
				Email, address, Post;    //�����������
			cout << "�밴˳�������" << i + 1
				<< "��ͬѧ��������Ժϵ���༶���ֻ�����ͥ�绰�������ʼ�����ͥ��ַ���ʱࣺ" << endl;
			cin >> Name >> College >> Class >> Tel >> Phone >> Email >> address >> Post;  //�����������

			Student* add = NULL;
			add = new Student(Name, College, Class, Tel, Phone, Email, address, Post);
			newSpace[this->number + i] = add;   //��ԭ�еĻ����ϼ������

		}
		delete[] this->m_StuArray;    //�ͷ�ԭ�пռ�
		this->Is_empty = false;      //�ļ���Ϊ��
		this->m_StuArray = newSpace;
		this->number = newNum;         //����ѧ������
		cout << "��ӳɹ���" << endl;
		this->Save();      //�����ݵ����ļ�
	}
	else
	{
		cout << "��������" << endl;
	}
	//������������ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}
void BookManager::show_Stu()
{
	if (this->Is_empty)
		cout << "�ļ�Ϊ�ջ򲻴��ڣ�" << endl;
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
int BookManager::Is_Exist(string name)   //�ж�ĳ���Ƿ����
{
	int flag = -1;

	for (int i = 0; i < this->number; i++)
	{
		if (this->m_StuArray[i]->m_Name == name)
		{
			flag = i;                //��λ�ñ���
			break;
		}
	}
	return flag;                 //����λ��
}
void BookManager::del_Stu()
{
	if (this->Is_empty) cout << "�ļ������ڻ�Ϊ�գ�" << endl;
	else
	{
		cout << "����������ɾ�������֣�" << endl;
		string name;
		int a[10];
		int num = 0;
		cin >> name;
		for (int i = 0; i < number; i++)
		{
			if (this->m_StuArray[i]->m_Name == name)
			{
				cout << "����ɾ����" << name << "����Ϣ���£�" << endl;
				this->m_StuArray[i]->showStudent();
				this->m_StuArray[i]->showAddress();
				a[num] = i;
				num++;
			}
		}

		if (num != 0)   //�����ͬѧ����
		{
			if (num > 1)
			{
				cout << "����������ɾ���˵�Ժϵ��" << endl;
				string col;
				cin >> col;
				for (int i = 0; i < num; i++)
				{
					if (this->m_StuArray[a[i]]->m_College == col)
					{
						for (int j = a[i]; j < this->number - 1; j++)
						{
							this->m_StuArray[j] = this->m_StuArray[j + 1];  //�������ݺ������ǰ��
						}
						this->number--;        //��������
						this->Save();        //��ɾ�������Ϣ���µ��ļ���
						cout << "ɾ���ɹ���" << endl;
						system("pause");
						system("cls");
					}
				}

			}
			else if (num == 1)
			{
				for (int i = a[0]; i < this->number - 1; i++)
				{
					this->m_StuArray[i] = this->m_StuArray[i + 1];  //�������ݺ������ǰ��
				}
				this->number--;        //��������
				this->Save();        //��ɾ�������Ϣ���µ��ļ���
				cout << "ɾ���ɹ���" << endl;
				system("pause");
				system("cls");
			}
		}
		else cout << "δ�ҵ���ͬѧ��" << endl;
	}
}

void BookManager::mod_Stu()
{
	if (this->Is_empty)   //�ļ�Ϊ��
	{
		cout << "�ļ������ڻ�Ϊ�գ�" << endl;
	}
	else
	{
		cout << "������Ҫ�޸ĵ�ͬѧ������" << endl;
		string name;
		cin >> name;
		int num = 0;
		int a[10];
		for (int i = 0; i < number; i++)
		{
			if (this->m_StuArray[i]->m_Name == name)
			{
				cout << "�����޸ģ�" << name << "����Ϣ���£�" << endl;
				this->m_StuArray[i]->showStudent();
				this->m_StuArray[i]->showAddress();
				a[num] = i;
				num++;
			}
		}
		if (num != 0)   //�����ͬѧ����
		{
			if (num > 1)
			{
				cout << "�����������޸��˵�Ժϵ��" << endl;
				string col;
				cin >> col;
				for (int i = 0; i < num; i++)
				{
					if (this->m_StuArray[a[i]]->m_College == col)
					{
						delete this->m_StuArray[a[i]];    //��Ҫ�޸ĵ�����ɾ��
						string College, Class, Tel, Phone,
							Email, address, Post;    //�����������
						cout << "�밴˳������" << name
							<< "ͬѧ���µ�Ժϵ���༶���ֻ�����ͥ�绰�������ʼ�����ͥ��ַ���ʱࣺ" << endl;
						cin >> College >> Class >> Tel >> Phone >> Email >> address >> Post;  //�����������

						Student* stu = NULL;
						stu = new Student(name, College, Class, Tel, Phone,
							Email, address, Post);
						this->m_StuArray[a[i]] = stu;
						cout << "�޸ĳɹ���" << endl;
						this->Save();      //���浽�ļ���
					}
				}

			}
			else if (num == 1)
			{
				delete this->m_StuArray[a[0]];    //��Ҫ�޸ĵ�����ɾ��
				string College, Class, Tel, Phone,
					Email, address, Post;    //�����������
				cout << "�밴˳������" << name
					<< "ͬѧ���µ�Ժϵ���༶���ֻ�����ͥ�绰�������ʼ�����ͥ��ַ���ʱࣺ" << endl;
				cin >> College >> Class >> Tel >> Phone >> Email >> address >> Post;  //�����������

				Student* stu = NULL;
				stu = new Student(name, College, Class, Tel, Phone,
					Email, address, Post);
				this->m_StuArray[a[0]] = stu;
				cout << "�޸ĳɹ���" << endl;
				this->Save();      //���浽�ļ���
			}
		}
		else cout << "δ�ҵ���ͬѧ��" << endl;
	}
	system("pause");
	system("cls");
}
void BookManager::find_Stu()
{
	if (this->Is_empty)   //�ļ�Ϊ��
	{
		cout << "�ļ������ڻ�Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��ѡ����ҷ�ʽ��" << endl;
		cout << "1.����������ѯ" << endl;
		cout << "2.����������ѧԺ��ѯ" << endl;
		int choice = 0;
		cin >> choice;
		if (choice == 1)     //��һ�ֶβ�ѯ
		{
			string name;
			int flag = 0;
			cout << "������Ҫ��ѯ��������" << endl;
			cin >> name;
			for (int i = 0; i < number; i++)
			{
				if (this->m_StuArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���" << name << "����Ϣ���£�" << endl;
					this->m_StuArray[i]->showStudent();
					this->m_StuArray[i]->showAddress();
					flag = 1;
				}
			}
			if (flag == 0)
				cout << "δ��ѯ�����˵���Ϣ��" << endl;
		}
		else if (choice == 2)    //���ֶ����ϲ�ѯ
		{
			string name, college;
			int flag = 0;
			cout << "������Ҫ��ѯ��������Ժϵ��" << endl;
			cin >> name >> college;
			for (int i = 0; i < number; i++)
			{
				if (this->m_StuArray[i]->m_Name == name && this->m_StuArray[i]->m_College == college)
				{
					cout << "���ҳɹ���" << name << "����Ϣ���£�" << endl;
					this->m_StuArray[i]->showStudent();
					this->m_StuArray[i]->showAddress();
					flag = 1;
				}
			}
			if (flag == 0)
				cout << "δ��ѯ�����˵���Ϣ��" << endl;
		}
		else cout << "��������" << endl;
	
	}
	system("pause");
	system("cls");
}
void BookManager::Save()
{
	ofstream out;
	out.open(Filename, ios::out);   //�������ʽ���ļ�
	for (int i = 0; i < this->number; i++)   //������д���ļ�
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
void BookManager::Exit_System()  //�˳�ϵͳ
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

BookManager::~BookManager()   //��������
{
	if (this->m_StuArray != NULL)
	{
		delete[] this->m_StuArray;        //��new���ٵĶ�������delete�ͷ�
		this->m_StuArray = NULL;
	}
}