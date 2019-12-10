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
	int dest;//�ߵ���һ�ߵĽڵ�
	int cost;//Ȩֵ
	Edge* next;
	Edge(int num, int cost) :dest(num), next(NULL),cost(cost) {};
};

struct Vertex
{
	bool flag;		//��־�Ƿ�ռ��
	string Name;	//·����IP
	Edge*first;//�������ͷָ��
	Vertex() :first(NULL),flag(0) {};
};

struct Route
{
	string dest;		//Ŀ��
	string gateway;		//��һ��
	int cost;
	Route(string s1, string s2) :dest(s1), gateway(s2), cost(0) {};
};

class Graph
{
public:
	Graph():NodeNum(0),NodeTable(NULL){};
	~Graph();
	void Dijkstra(int v);		//�Խڵ���·�ɱ�
	void Init();				//��ʼ����һ���Խ�ͼ
	void clear();
	//friend ostream & operator<<(ostream& os, Graph & A);
	//friend istream & operator>>(istream& is, Graph & A);
	bool insertVertex(string Name);		//�ӵ�
	void insertEdge(int v1, int v2, int cost);	//�ӱ�
	bool insertEdge(string v1, string v2, int cost);	//�ӱ�
	void deleteVertex(int v);			//ɾ��
	void deleteVertex(string v);			//ɾ��
	void deleteEdge(int v1, int v2);	//ɾ��
	bool deleteEdge(string v1, string v2);	//ɾ��
	bool findV(string str);			//�������ҵ�
private:
	Vertex*NodeTable;//ͼ�ڵ��
	int NodeNum;	 //�ڵ����
};
#endif // !GRAPH_H
