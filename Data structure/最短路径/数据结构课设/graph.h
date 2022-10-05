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

//初始化
void initGraph(MGraph* pGraph);
//生成图
void createGraph(MGraph* pGraph);
//展示图的邻接矩阵
void showGraph(MGraph pGraph);
//画图
void drawGraph(MGraph pGraph);
//DFS(深度优先搜索)
void DFSTraverse(MGraph pGraph);
//DFS
void DFS(MGraph pGraph, int* pVisited, int i);
//BFS（广度优先搜索）
void BFSTraverse(MGraph pGraph);
//最小生成树（）
void MinimumSpanningTree(MGraph pGraph);
//普里姆算法
void Prim(MGraph pGraph);
EdgeWight* sortEdgeWight(MGraph pGraph);
//克鲁斯卡尔
void Kruskal(MGraph pGraph);