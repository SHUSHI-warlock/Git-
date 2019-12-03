#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include<stdio.h>
#include<string>

struct Edge
{
	int dest;//边的另一边的节点
	int cost;//权值
	Edge* next;
	Edge(int num, int cost) :dest(num), next(NULL),cost(cost) {};
};

struct Vertex
{
	string Name;	//路由器名字
	Edge*first;//边链表的头指针
	Vertex() :first(NULL) {};
};

class Graph
{
public:
	Graph():NodeNum(0),NodeTable(NULL){};
	~Graph();
	int Dijiesita(int v);		//对节点求路由表
	void Init();				//初始化，一次性建图
	void clear();
	//friend ostream & operator<<(ostream& os, Graph & A);
	//friend istream & operator>>(istream& is, Graph & A);
	void insertVertex(string Name);		//加点
	void insertEdge(int v1, int v2, int cost);	//加边
private:
	Vertex*NodeTable;//图节点表
	int NodeNum;	 //节点个数
};
#endif // !GRAPH_H
