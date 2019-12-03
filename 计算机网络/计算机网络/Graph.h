#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include<stdio.h>
#include<math.h>
#include <iostream>
#include <algorithm>
#include<cstring>
#include<string>
#include<stack>
#include<queue>

using namespace std;
struct Edge
{
	int dest;//�ߵ���һ�ߵĽڵ�
	int cost;//Ȩֵ
	Edge* next;
	Edge(int num, int ways) :dest(num), next(NULL),cost(0) {};
};

struct Vertex
{
	string Name;	//·��������
	Edge*first;//�������ͷָ��
	Vertex() :first(NULL) {};
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
	void insertVertex(int x, int y);		//�ӵ�
	void insertEdge(int v1, int v2, int cost);	//�ӱ�
private:
	Vertex*NodeTable;//ͼ�ڵ��
	int NodeNum;	 //�ڵ����
};


#endif // !GRAPH_H
