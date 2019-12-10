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

struct Route
{
	unsigned int dest[4];		//Ŀ��
	//unsigned int mask[4];		//����
	unsigned int next[4];		//��һ��
	//int interface;			//����
	int cost;					//Ȩֵ
};

struct Vertex
{
	bool flag;		//��־�Ƿ�ռ��
	unsigned int Name[4];	//·����IP
	Edge*first;//�������ͷָ��
<<<<<<< HEAD
	Vertex() :first(NULL),flag(0) {};
};

struct Route
{
	string dest;		//Ŀ��
	string gateway;		//��һ��
	int cost;
	Route(string s1, string s2) :dest(s1), gateway(s2), cost(0) {};
=======
	Route*R;
	Vertex() :first(NULL) {};
>>>>>>> dd56904958774f3e52590c13475fb2ba1df59b16
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
<<<<<<< HEAD
	bool insertVertex(string Name);		//�ӵ�
=======
	bool insertVertex(int []);		//�ӵ�
>>>>>>> dd56904958774f3e52590c13475fb2ba1df59b16
	void insertEdge(int v1, int v2, int cost);	//�ӱ�
	bool insertEdge(string v1, string v2, int cost);	//�ӱ�
	void deleteVertex(int v);			//ɾ��
	bool deleteVertex(string v);			//ɾ��
	void deleteEdge(int v1, int v2);	//ɾ��
	bool deleteEdge(string v1, string v2);	//ɾ��
	int findV(string str);			//�������ҵ�
private:

	Vertex*NodeTable;//ͼ�ڵ��
	int NodeNum;	 //�ڵ����
};
#endif // !GRAPH_H
