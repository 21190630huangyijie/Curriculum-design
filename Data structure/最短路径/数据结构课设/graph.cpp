
#include "graph.h"
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <queue>
#include <malloc.h>
#include <algorithm>
#include<cstring>
#include<string>
using namespace std;
int v = 0;
void Print(int i)
{
	switch (i) {
	case 0:printf("�Ͼ�"); break;
	case 1:printf("������"); break;
	case 2:printf("����"); break;
	case 3:printf("��³ľ��"); break;
	case 4:printf("����"); break;
	case 5:printf("����"); break;
	case 6:printf("����"); break;
	case 7:printf("����"); break;
	case 8:printf("����"); break;
	case 9:printf("�ɶ�"); break;
	case 10:printf("�人"); break;
	}
}
void initGraph(MGraph* pGraph)
{
	for (int i = 0; i < pGraph->vertexNum; ++i)
	{
		for (int j = 0; j < pGraph->vertexNum; ++j)
		{
			if (i != j)
			{
				pGraph->graphEdge[i][j] = MINFINITE;
			}
			else
			{
				pGraph->graphEdge[i][j] = 0;
			}
		}
	}
}

void createGraph(MGraph* pGraph)
{
	FILE* fp(fopen("Graph.txt", "r"));
	fscanf(fp, "%d,%d\n", &pGraph->vertexNum, &pGraph->edgeNum);
	initGraph(pGraph);
	for (int i = 0; i < pGraph->vertexNum; ++i)
	{
		fscanf(fp, "%c,%d,%d\n", &pGraph->graphVertex[i].data, &pGraph->graphVertex[i].x, &pGraph->graphVertex[i].y);
	}
	int i, j, wight;
	for (int k = 0; k < pGraph->edgeNum; ++k)
	{
		fscanf(fp, "%d,%d,%d\n", &i, &j, &wight);
		pGraph->graphEdge[i][j] = wight;
		pGraph->graphEdge[j][i] = wight;
	}
	fclose(fp);
}

void showGraph(MGraph pGraph)
{
	printf("������:%d,������%d\n�������ƣ�", pGraph.vertexNum, pGraph.edgeNum);
	for (int i = 0; i < pGraph.vertexNum; ++i)
	{
		printf("%c,", pGraph.graphVertex[i]);
	}
	puts("\n��Ӿ���");
	for (int i = 0; i < pGraph.vertexNum; ++i)
	{
		for (int j = 0; j < pGraph.vertexNum; ++j)
		{
			if (pGraph.graphEdge[i][j] == MINFINITE)
			{
				printf("*  ");
			}
			else
			{
				printf("%-3d", pGraph.graphEdge[i][j]);
			}
		}
		puts("");
	}
}

void drawGraph(MGraph pGraph)
{
	initgraph(862, 583,SHOWCONSOLE);
	IMAGE img;
	loadimage(&img, L"D:\\ѧϰ����\\���ݽṹ�γ����\\���ݽṹ����\\���ݽṹ����/chinamap1.jpg");
	putimage(0, 0, &img);
	int x1, y1, x2, y2;
	setlinecolor(RGB(255, 0, 0));
	setlinestyle(0, 3, 0);
	wchar_t str[100];
	for (int i = 1; i < pGraph.vertexNum; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (pGraph.graphEdge[i][j] > 0 && pGraph.graphEdge[i][j] < MINFINITE)
			{
				x1 = pGraph.graphVertex[i].x;
				y1 = pGraph.graphVertex[i].y;
				x2 = pGraph.graphVertex[j].x;
				y2 = pGraph.graphVertex[j].y;
				line(x1, y1, x2, y2);
				swprintf(str, _T("%d"), pGraph.graphEdge[i][j]);
				outtextxy((x1 + x2 - 10) / 2, (y1 + y2 - 20) / 2, (LPCTSTR)str);
				//outtextxy((x1 + x2 + 20) / 2, (y1 + y2 + 20) / 2, (LPCTSTR)str);
			}
		}
	}
	setfillcolor(RGB(0, 0, 255));
	int radio = 8;
	for (int i = 0; i < pGraph.vertexNum; ++i)
	{
		fillcircle(pGraph.graphVertex[i].x, pGraph.graphVertex[i].y, radio);
		//outtextxy(pGraph.graphVertex[i].x - 5, pGraph.graphVertex[i].y - 5, pGraph.graphVertex[i].data);
	}
	MinimumSpanningTree(pGraph);
	_getch();
	//closegraph();
}


void Dijkstra(MGraph pGraph)
{
	//��¼���·����ֵ������
	int shortesPath[MAXVEX];
	int visitVertex[MAXVEX];
	//��¼ʹ�ù�����ļ���
	int fromVertex[MAXVEX];
	int x1, x2, y1, y2;
	setlinecolor(RGB(255, 255, 0));
	setlinestyle(0,3,0);
	for (int i = 0; i < pGraph.vertexNum; ++i)
	{
		shortesPath[i] = pGraph.graphEdge[v][i];
		fromVertex[i] = v;
		visitVertex[i] = 0;
	}
	visitVertex[v] = 1;
	for (int i = 1; i < pGraph.vertexNum; ++i)
	{
		int minWight = MINFINITE;
		int min = -1;
		for (int j = 0; j < pGraph.vertexNum; ++j)
		{
			if (visitVertex[j] == 0 && minWight > shortesPath[j])
			{
				minWight = shortesPath[j];
				min = j;
			}
		}
		visitVertex[min] = 1;
		for (int j = 0; j < pGraph.vertexNum; ++j)
		{
			if (pGraph.graphEdge[min][j] != MINFINITE)
			{
				if (!visitVertex[j]&&shortesPath[min] + pGraph.graphEdge[min][j] < shortesPath[j])
				{
					shortesPath[j] = shortesPath[min] + pGraph.graphEdge[min][j];
					fromVertex[j] = min;
				}
			}
		}
	}
	printf("���·��ʱ�䣺\n");
	for (int i = 0; i < pGraph.vertexNum; ++i)
	{
		printf("%-3d ", shortesPath[i]);
	}
	/*
	printf("\n�������У�\n");
	for (int i = 0; i < pGraph.vertexNum; ++i)
	{
		//printf("%-3d ", fromVertex[i]);
		Print(fromVertex[i]);
		printf(" ");
	}
	printf("\n");
	*/
	printf("\n");
	printf("\n");
	for (int i = 0; i < pGraph.vertexNum; ++i)
	{
		setlinecolor(RGB(255, 255, 0));
		setlinestyle(0, 3, 0);
		if (i != v)
		{
			int j = i;
			int k = i;
			//printf("%c--->", pGraph.graphVertex[i].data);
			Print(i);
			printf("--->");
			while (fromVertex[j] != v)
			{
				//printf("%c---->", pGraph.graphVertex[fromVertex[j]].data);
				Print(fromVertex[j]);
				printf("--->");
				j = fromVertex[j];
				_getch();
				x1 = pGraph.graphVertex[k].x;
				y1 = pGraph.graphVertex[k].y;
				x2 = pGraph.graphVertex[j].x;
				y2 = pGraph.graphVertex[j].y;
				line(x1, y1, x2, y2);
				k = j;
			}
			//printf("%c\n", pGraph.graphVertex[v].data);
			Print(v);
			printf("    ���·��ʱ�䣺%-3d ", shortesPath[i]);
			printf("\n");
			_getch();
			x1 = pGraph.graphVertex[v].x;
			y1 = pGraph.graphVertex[v].y;
			x2 = pGraph.graphVertex[j].x;
			y2 = pGraph.graphVertex[j].y;
			line(x1, y1, x2, y2);
			
		}
		_getch();
		setlinecolor(RGB(255, 0, 0));
		//wchar_t str[100];
		for (int m = 1; m < pGraph.vertexNum; ++m)
		{
			for (int n = 0; n < m; ++n)
			{
				if (pGraph.graphEdge[m][n] > 0 && pGraph.graphEdge[m][n] < MINFINITE)
				{
					x1 = pGraph.graphVertex[m].x;
					y1 = pGraph.graphVertex[m].y;
					x2 = pGraph.graphVertex[n].x;
					y2 = pGraph.graphVertex[n].y;
					line(x1, y1, x2, y2);
					//swprintf(str, _T("%d"), pGraph.graphEdge[i][j]);
					//outtextxy((x1 + x2 - 10) / 2, (y1 + y2 - 20) / 2, (LPCTSTR)str);
				}
			}
		}
		setfillcolor(RGB(0, 0, 255));
		int radio = 8;
		for (int i = 0; i < pGraph.vertexNum; ++i)
		{
			fillcircle(pGraph.graphVertex[i].x, pGraph.graphVertex[i].y, radio);
			//outtextxy(pGraph.graphVertex[i].x - 5, pGraph.graphVertex[i].y - 5, pGraph.graphVertex[i].data);
		}
	}
}

void MinimumSpanningTree(MGraph pGraph)
{

	Dijkstra(pGraph);
}
int main()
{
	MGraph graph;
	createGraph(&graph);
	//showGraph(graph);
	printf("0:�Ͼ� 1:������ 2:���� 3:��³ľ�� 4:���� 5:���� 6:���� 7:���� 8:���� 9:�ɶ� 10:�人\n");
	printf("������Ŀ�ĵش������֣�\n");
	scanf("%d", &v);
	drawGraph(graph);
	system("pause");
	return 0;
}