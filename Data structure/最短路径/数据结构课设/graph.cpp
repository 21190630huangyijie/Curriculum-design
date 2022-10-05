
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
	case 0:printf("南京"); break;
	case 1:printf("哈尔滨"); break;
	case 2:printf("北京"); break;
	case 3:printf("乌鲁木齐"); break;
	case 4:printf("拉萨"); break;
	case 5:printf("昆明"); break;
	case 6:printf("南宁"); break;
	case 7:printf("广州"); break;
	case 8:printf("福州"); break;
	case 9:printf("成都"); break;
	case 10:printf("武汉"); break;
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
	printf("顶点数:%d,边数：%d\n顶点名称：", pGraph.vertexNum, pGraph.edgeNum);
	for (int i = 0; i < pGraph.vertexNum; ++i)
	{
		printf("%c,", pGraph.graphVertex[i]);
	}
	puts("\n领接矩阵：");
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
	loadimage(&img, L"D:\\学习资料\\数据结构课程设计\\数据结构课设\\数据结构课设/chinamap1.jpg");
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
	//记录最短路径的值的数组
	int shortesPath[MAXVEX];
	int visitVertex[MAXVEX];
	//记录使用过顶点的集合
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
	printf("最短路径时间：\n");
	for (int i = 0; i < pGraph.vertexNum; ++i)
	{
		printf("%-3d ", shortesPath[i]);
	}
	/*
	printf("\n经过城市：\n");
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
			printf("    最短路径时间：%-3d ", shortesPath[i]);
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
	printf("0:南京 1:哈尔滨 2:北京 3:乌鲁木齐 4:拉萨 5:昆明 6:南宁 7:广州 8:福州 9:成都 10:武汉\n");
	printf("请输入目的地代表数字：\n");
	scanf("%d", &v);
	drawGraph(graph);
	system("pause");
	return 0;
}