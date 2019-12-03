#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include<stdio.h>
#include<string>
using namespace std;
const int MaxNum = 30;

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

class Graph
{
public:
	Graph():NodeNum(0),NodeTable(NULL){};
	~Graph();
	int Dijiesita(int v);		//�Խڵ���·�ɱ�
	void Init();				//��ʼ����һ���Խ�ͼ
	void clear();
	//friend ostream & operator<<(ostream& os, Graph & A);
	//friend istream & operator>>(istream& is, Graph & A);
	bool insertVertex(string Name);		//�ӵ�
	void insertEdge(int v1, int v2, int cost);	//�ӱ�
	void deleteVertex(int v);			//ɾ��
	void deleteEdge(int v1, int v2);	//ɾ��
private:
	Vertex*NodeTable;//ͼ�ڵ��
	int NodeNum;	 //�ڵ����
};
#endif // !GRAPH_H
