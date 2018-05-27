#ifndef HEADER_H
#define HEADER_H 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h> 
#include<iostream>
using namespace std;
#define UNVISITED 0			//δ������ 
#define VISITED 1			//������ 
#define UNSELECTED 0		//δ��ѡ�� 
#define SELECTED 1			//��ѡ�� 
#define INFINITY INT_MAX	//�����������������ֵ 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define MaxSize 10
#define NOLINK 0

typedef int Status;
typedef struct{
	int n;				//������� 
	int e;				//�ߵĸ��� 
	int *tags;			//����״̬���� 
	int **arcs;			//��ϵ����
	char *vexs;			//�������� 
}Graph;
typedef struct{
	char v;				//�ߵ���� 
	char w;				//�ߵ��յ� 
}ArcInfo;	
typedef struct DistInfo{
	int prev;			//��ǰ���·���ϸö����ǰ������λ�� 
	int shortest;		//��ǰ���·������ 
}DistInfo,*pDistInfo; 

Status CreateVexs(char *vexs);											//������������
Status CreateArcs(ArcInfo *arcs,int n);									//������ϵ����
int LocateVex(Graph G,char v);											//��ȡ������Ӧ��λ��
int FirstAdjVex(Graph G,int k);											//Ѱ�ҵ�һ���ڽӽڵ�
int NextAdjVex(Graph G,int k,int m);									//Ѱ����һ���ڽӽڵ�
Status InitGraph(Graph &G,char *vexs,int n,ArcInfo *arcs,int e);		//��ʼ��·�ɱ�
Status CreateGraph(Graph &G,ArcInfo *arcs);								//����·�ɱ�
Status Dijkstra(Graph G,int i,pDistInfo &Dist);							//�Ͻ�˹�����㷨Ѱ�����·��
char NextJump(Graph G,DistInfo *Dist,int k);							//Ѱ��·��������һ��
void PrintRoute(Graph G,DistInfo *Dist,int k);							//������·��·��
Status OutputGraph(Graph &G,int VEXSSIZE);							//���·������ͼ
Status OutputRoute(Graph &G,int VEXSSIZE);							//������ڵ��·����Ϣ 
#endif 
