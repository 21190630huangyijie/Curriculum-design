#pragma once
#define MAXVEX 100
#define MINFINITE 0x7FFFFFFF
typedef int EdgeType;

typedef struct
{
	int edgeBegin;
	int edgeEnd;
	int wight;
}EdgeWight;

typedef struct
{
	char data;
	int x;
	int y;
}Vertex;

typedef struct
{
	Vertex graphVertex[MAXVEX];
	EdgeType graphEdge[MAXVEX][MAXVEX];
	int vertexNum;
	int edgeNum;
}MGraph;

//��ʼ��
void initGraph(MGraph* pGraph);
//����ͼ
void createGraph(MGraph* pGraph);
//չʾͼ���ڽӾ���
void showGraph(MGraph pGraph);
//��ͼ
void drawGraph(MGraph pGraph);
//DFS(�����������)
void DFSTraverse(MGraph pGraph);
//DFS
void DFS(MGraph pGraph, int* pVisited, int i);
//BFS���������������
void BFSTraverse(MGraph pGraph);
//��С����������
void MinimumSpanningTree(MGraph pGraph);
//����ķ�㷨
void Prim(MGraph pGraph);
EdgeWight* sortEdgeWight(MGraph pGraph);
//��³˹����
void Kruskal(MGraph pGraph);