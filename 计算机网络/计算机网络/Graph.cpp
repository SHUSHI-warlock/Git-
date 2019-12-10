#include"pch.h"
#include"Graph.h"

#include<cstdio>
#include<string>
#include<cmath>
#include <algorithm>
#include <iostream>
#include<cstring>
#include<stack>
#include<queue>
#include<fstream>

//��������
Graph::~Graph()
{
	clear();
}
//���ͼ
void Graph::clear()
{
	//�ͷŽڵ�ͱ�
	Edge*Temp, *current;
	for (int i = 0; i < NodeNum; i++)
	{
		current = NodeTable[i].first;
		while (current != NULL)
		{
			Temp = current;
			current = current->next;
			delete Temp;
		}
	}
	delete[]NodeTable;
	NodeTable = NULL;
	NodeNum = 0;
}
//�ҵ�
bool findV(string str)
{

}
//�ӵ�
bool Graph::insertVertex(string Name)
{
	if (NodeNum < MaxNum)	//˳�����
	{
		NodeTable[NodeNum].flag = 1;
		NodeTable[NodeNum].Name = Name;
		NodeTable[NodeNum].first = NULL;
		NodeNum++;
		return true;
	}
	else
	{
		for (int i = 0; i < MaxNum; i++)
		{
			if (NodeTable[i].flag == 0)
			{
				NodeTable[i].flag = 1;
				NodeTable[i].Name = Name;
				NodeTable[i].first = NULL;
				return true;
			}
		}
	}
	return false;
}
//�ӱ�
void Graph::insertEdge(int v1, int v2, int cost)
{
	Edge*current;

	current = NodeTable[v1].first;
	NodeTable[v1].first = new Edge(v2, cost);	//�ײ巨
	NodeTable[v1].first->next = current;

	current = NodeTable[v2].first;
	NodeTable[v2].first = new Edge(v1, cost);
	NodeTable[v2].first->next = current;
}
bool Graph::insertEdge(string v1, string v2, int cost)
{
	int V1, V2;
	int yes = 2;
	for (int i = 0; i < NodeNum; i++) {
		if (NodeTable[i].Name == v1){
			V1 = i; yes--;
		}
		else if (NodeTable[i].Name == v2){
			V2 = i; yes--;
		}
		if (!yes)
			break;
	}
	if (!yes) {
		insertEdge(V1, V2, cost);
		return true;
	}
	else
		cout << "�����������㣡" << endl;
	return false;
}

//ɾ��
void Graph::deleteVertex(int v)				//ɾ��
{
	//ɾ���õ��������ıߵ���Ϣ
	Edge* current,*temp,*last;
	current = NodeTable[v].first;
	while (current!=NULL)
	{
			//ɾ������������һ���ڵ��е�������
		int m = current->dest;
		temp= NodeTable[m].first;
		if (temp->dest == v)
		{
			NodeTable[m].first = temp->next;
			delete temp;
			temp = NULL;
		}
		else
		{
			last = temp;
			temp = temp->next;
			while (temp != NULL)
			{
				if (temp->dest == v)
				{
					last->next = temp->next;
					delete temp;
					break;
				}
				last = temp;
				temp = temp->next;
			}	
			last = temp = NULL;
		}
			//ɾ����ǰ�ڵ����������
		temp = current;
		current = current->next;
		delete temp;
	}
	temp = NULL;

	//ɾ����
	//NodeTable[v].Name;
	NodeTable[v].first = NULL;
	NodeTable[v].flag = 0;
}
//ɾ��
void Graph::deleteEdge(int v1, int v2)		//ɾ��
{
	Edge* current, *last;
	//��v1��ɾ��v2
	current = NodeTable[v1].first;
	if (current->dest == v2)
	{
		NodeTable[v1].first = current->next;
		delete current;
	}
	else
	{
		last = current;
		current = current->next;
		while (current != NULL)
		{
			if (current->dest == v2)
			{
				last->next = current->next;
				delete current;
				break;
			}
			last = current;
			current = current->next;
		}
		last = current = NULL;
	}
	//��v1��ɾ��v1
	current = NodeTable[v2].first;
	if (current->dest == v1)
	{
		NodeTable[v2].first = current->next;
		delete current;
	}
	else
	{
		last = current;
		current = current->next;
		while (current != NULL)
		{
			if (current->dest == v1)
			{
				last->next = current->next;
				delete current;
				break;
			}
			last = current;
			current = current->next;
		}
		last = current = NULL;
	}
}
bool Graph::deleteEdge(string v1, string v2)		//ɾ��
{
	int V1, V2;
	int yes = 2;
	for (int i = 0; i < NodeNum; i++) {
		if (NodeTable[i].Name == v1) {
			V1 = i; yes--;
		}
		else if (NodeTable[i].Name == v2) {
			V2 = i; yes--;
		}
		if (!yes)
			break;
	}
	if (!yes) {
		deleteEdge(V1, V2);
		return true;
	}
	else
		cout << "�����������㣡" << endl;
	return false;
}
//��ʼ��
void Graph::Init()
{
	ofstream os;
	os.open("text.txt");
	int v, e;
	os << v << e;
	int cost;
	string str1, str2;
	for (int i = 0; i < v; i++)
	{
		os << str1;
		insertVertex(str1);
	}
	for (int i = 0; i < e; i++)
	{
		os << str1 << str2 << cost;
		insertEdge(str1, str2, cost);
	}
	for(int i=0;i<v)
	Dijkstra()
}


