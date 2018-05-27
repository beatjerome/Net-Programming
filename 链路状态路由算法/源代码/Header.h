#ifndef HEADER_H
#define HEADER_H 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h> 
#include<iostream>
using namespace std;
#define UNVISITED 0			//未被访问 
#define VISITED 1			//被访问 
#define UNSELECTED 0		//未被选择 
#define SELECTED 1			//被选择 
#define INFINITY INT_MAX	//计算机允许的整数最大值 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define MaxSize 10
#define NOLINK 0

typedef int Status;
typedef struct{
	int n;				//顶点个数 
	int e;				//边的个数 
	int *tags;			//访问状态数组 
	int **arcs;			//关系数组
	char *vexs;			//顶点数组 
}Graph;
typedef struct{
	char v;				//边的起点 
	char w;				//边的终点 
}ArcInfo;	
typedef struct DistInfo{
	int prev;			//当前最短路径上该顶点的前驱顶点位序 
	int shortest;		//当前最短路径长度 
}DistInfo,*pDistInfo; 

Status CreateVexs(char *vexs);											//创建顶点数组
Status CreateArcs(ArcInfo *arcs,int n);									//创建关系数组
int LocateVex(Graph G,char v);											//获取顶点相应的位序
int FirstAdjVex(Graph G,int k);											//寻找第一个邻接节点
int NextAdjVex(Graph G,int k,int m);									//寻找下一个邻接节点
Status InitGraph(Graph &G,char *vexs,int n,ArcInfo *arcs,int e);		//初始化路由表
Status CreateGraph(Graph &G,ArcInfo *arcs);								//创建路由表
Status Dijkstra(Graph G,int i,pDistInfo &Dist);							//迪杰斯特拉算法寻找最短路径
char NextJump(Graph G,DistInfo *Dist,int k);							//寻找路由器的下一跳
void PrintRoute(Graph G,DistInfo *Dist,int k);							//输出最短路由路径
Status OutputGraph(Graph &G,int VEXSSIZE);							//输出路由拓扑图
Status OutputRoute(Graph &G,int VEXSSIZE);							//输出各节点的路由信息 
#endif 
