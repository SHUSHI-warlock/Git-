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
	Route* R;
	Vertex() :first(NULL),flag(0),R(NULL) {};
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
	bool insertVertex(int name[]);					//�ӵ�
	void insertEdge(int v1, int v2, int cost);		//�ӱ�
	bool insertEdge(int v1[], int v2[], int cost);	//�ӱ�
	void deleteVertex(int v);						//ɾ��
	bool deleteVertex(int name[]);					//ɾ��
	void deleteEdge(int v1, int v2);				//ɾ��
	bool deleteEdge(int v1[], int v2[]);			//ɾ��
	void Print(int name[]);							//���
	void Print();
	void Update();                                  //����
	int findV(int name[]);							//�������ҵ�
private:
	Vertex*NodeTable;//ͼ�ڵ��
	int NodeNum;	 //�ڵ����
};
#endif // !GRAPH_H
