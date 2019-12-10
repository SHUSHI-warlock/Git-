#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include<cstdio>
#include<string>
using namespace std;
const int MaxNum = 30;
using namespace std;
struct Edge
{
	int dest;//边的另一边的节点
	int cost;//权值
	Edge* next;
	Edge(int num, int cost) :dest(num), next(NULL),cost(cost) {};
};

struct Route
{
	unsigned int dest[4];		//目的
	//unsigned int mask[4];		//掩码
	unsigned int next[4];		//下一跳
	//int interface;			//出口
	int cost;					//权值

};

struct Vertex
{
	bool flag;		//标志是否占有
	unsigned int Name[4];	//路由器IP
	Edge*first;//边链表的头指针
	Route* R;
	Vertex() :first(NULL),flag(0),R(NULL) {};
};

class Graph
{
public:
	Graph():NodeNum(0),NodeTable(NULL){};
	~Graph();
	void Dijkstra(int v);		//对节点求路由表
	void Init();				//初始化，一次性建图
	void clear();
	//friend ostream & operator<<(ostream& os, Graph & A);
	//friend istream & operator>>(istream& is, Graph & A);
	bool insertVertex(int name[]);					//加点
	void insertEdge(int v1, int v2, int cost);		//加边
	bool insertEdge(int v1[], int v2[], int cost);	//加边
	void deleteVertex(int v);						//删点
	bool deleteVertex(int name[]);					//删点
	void deleteEdge(int v1, int v2);				//删边
	bool deleteEdge(int v1[], int v2[]);			//删边
	void Print(int name[]);							//输出
	void Print();
	void Update();                                  //更新
	int findV(int name[]);							//给名字找点
private:
	Vertex*NodeTable;//图节点表
	int NodeNum;	 //节点个数
};
#endif // !GRAPH_H
