#include <iostream>
#include <fstream>
#include <time.h>
#include "Sort.h"
#define N 10000
using namespace std;
void SetData()
{
    fstream fout("data.txt", ios::out);
    if (!fout)
    {
        cout << "无法打开文件！" << endl;
        exit(1);
    }
    else
    {
        srand((unsigned)time(NULL));
        for (int i = 0; i < N; i++)
        {
            int m = rand() % N;
            fout << m << " ";
            if ((i + 1) % 20 == 0)
                fout << endl;
        }
        cout << "10000个随机数生成完毕!" << endl;
    }
    fout.close();
}

//写入文件
void WriteFile(int r[], int n, const char* filename)
{
    fstream fout(filename, ios::out);
    if (!fout)
    {
        cout << "无法打开文件！" << endl;
        exit(1);
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            fout << r[i] << " ";
            if ((i + 1) % 15 == 0)
                fout << endl;// '\n';
        }
    }
    fout.close();
}

//读取文件
int* ReadFile(int n, const char* filename)
{
    fstream fin(filename, ios::in);
    int* s = new int[n];

    if (!fin)
    {
        cout << "无法打开文件！" << endl;
        exit(1);
    }
    else
    {
        for (int i = 0; i < n; i++)
            fin >> s[i];
    }
    fin.close();
    return s;
}

void Menu()
{
    while (1)
    {
        system("cls");
        cout << "*************************************************" << endl;
        cout << "********************* 菜单 **********************" << endl;
        cout << "************ 0.退出               ***************" << endl;
        cout << "************ 1.建立原始数据       ***************" << endl;
        cout << "************ 2.希尔排序           ***************" << endl;
        cout << "************ 3.快速排序           ***************" << endl;
        cout << "************ 4.堆排序             ***************" << endl;
        cout << "************ 5.归并排序           ***************" << endl;
        cout << "*************************************************" << endl;
        cout << endl;
        cout << "请按照菜单上提示输入数字：" << endl;
        int choose = 0;
        cin >> choose;
        cout << endl;
        switch (choose)
        {
        case 0:
            exit(0);
        case 1:
            SetData();
            break;
        case 2:
        {
            int* r = ReadFile(N, "data.txt");
            ShellSort(r, N);
            WriteFile(r, N, "ShellSort.txt");
            cout << "ShellSort Success!" << endl;
            break;
        }
        case 3:
        {
            int* r = ReadFile(N, "data.txt");
            QuickSort(r, 0, N - 1);
            WriteFile(r, N, "QuickSort.txt");
            cout << "QuickSort Success!" << endl;
            break;
        }
        case 4:
        {
            int* r = ReadFile(N, "data.txt");
            HeapSort(r, N);
            WriteFile(r, N, "HeapSort.txt");
            cout << "HeapSort Success!" << endl;
            break;
        }
        case 5:
        {
            int* r = ReadFile(N, "data.txt");
            MergeSort(r, N);
            WriteFile(r, N, "MergeSort.txt");
            cout << "MergeSort Success!" << endl;
            break;
        }

        }
        system("pause");
    }
}

int main()
{
    Menu();
    return 0;
}