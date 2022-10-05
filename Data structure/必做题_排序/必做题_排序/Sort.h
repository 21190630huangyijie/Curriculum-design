#pragma once
#include <iostream>
#include <time.h>
#include <windows.h>
using namespace std;

//Ï£¶ûÅÅÐòËã·¨
void ShellSort(int r[], int n)
{
    for (int d = n / 2; d >= 1; d = d / 2)
    {
        for (int i = d; i < n; i++)
        {
            int temp = r[i];
            int j;

            for (j = i - d; j >= 0 && temp < r[j]; j = j - d)
                r[j + d] = r[j];
            r[j + d] = temp;
        }
    }
}

//¿ìËÙÅÅÐò           
int Partition(int r[], int i, int j)
{
    int temp = r[i];
    while (i < j)
    {
        while (i < j && r[j] >= temp)
            j--;
        if (i < j)
            r[i++] = r[j];
        while (i < j && r[i] <= temp)
            i++;
        if (i < j)
            r[j--] = r[i];
    }
    r[i] = temp;
    return i;
}

void QuickSort(int  r[], int i, int j)
{
    if (i < j)
    {
        int pivot = Partition(r, i, j);
        QuickSort(r, i, pivot - 1);
        QuickSort(r, pivot + 1, j);
    }
}

//¶ÑÅÅÐòÖÐµÄÉ¸Ñ¡Ëã·¨
void Sift(int  r[], int k, int m)
{
    int i = k;
    int j = 2 * i + 1;                      

    while (j <= m)                         
    {
        if (j < m && r[j] < r[j + 1])
            j++;                          
        if (r[i] > r[j])
            break;                        
        else
        {
            int temp = r[i];
            r[i] = r[j];
            r[j] = temp;
            i = j;
            j = i * 2 + 1;              
        }
    }
}

//¶ÑÅÅÐòËã·¨
void HeapSort(int r[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)    
        Sift(r, i, n - 1);
    for (int i = 1; i < n; i++)            
    {
        int temp = r[0];
        r[0] = r[n - i];
        r[n - i] = temp;
        Sift(r, 0, n - i - 1);
    }
}

//Ò»´Î¹é²¢Ëã·¨
void Merge(int r[], int r1[], int s, int m, int t)
{
    int i = s;
    int j = m + 1;
    int k = s;

    while (i <= m && j <= t)
        if (r[i] <= r[j])
            r1[k++] = r[i++];              
        else
            r1[k++] = r[j++];
    if (i <= m)
        while (i <= m)
            r1[k++] = r[i++];                 
    else
        while (j <= t)
            r1[k++] = r[j++];            
}

//Ò»ÌË¹é²¢ÅÅÐòËã·¨
void MergePass(int r[], int r1[], int n, int h)
{
    int i = 0;

    while (i <= n - 2 * h + 1)                   
    {
        Merge(r, r1, i, i + h - 1, i + 2 * h - 1);
        i += 2 * h;
    }
    if (i < n - h + 1)
        Merge(r, r1, i, i + h - 1, n);        
    else
        for (int k = i; k <= n; k++)
            r1[k] = r[k];                
}

//¹é²¢ÅÅÐòµÄ·ÇµÝ¹éËã·¨
void MergeSort(int r[], int n)
{
    int h = 1;
    int* r1 = new int[n];

    while (h < n)
    {
        MergePass(r, r1, n - 1, h);
        h = 2 * h;
        MergePass(r1, r, n - 1, h);
        h = 2 * h;
    }
}
