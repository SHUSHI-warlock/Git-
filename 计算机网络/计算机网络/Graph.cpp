#include"pch.h"
#include"Graph.h"

#include<cstdio>
#include<cmath>
#include<cstring>
#include <algorithm>
#include <iostream>
#include<string>
#include<stack>
#include<queue>
#include<fstream>

<<<<<<< HEAD
//��������
=======

>>>>>>> dd56904958774f3e52590c13475fb2ba1df59b16
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
<<<<<<< HEAD
//�ҵ�
int Graph::findV(string str)
{
	for (int i = 0; i < NodeNum; i++)
		if (NodeTable[i].Name == str)
			return i;
	return -1;
}
//�ӵ�
bool Graph::insertVertex(string Name)
=======
bool Graph::insertVertex(int Name[])
>>>>>>> dd56904958774f3e52590c13475fb2ba1df59b16
{
	if (NodeNum < MaxNum)	//˳�����
	{
		NodeTable[NodeNum].flag = 1;
		for (int i = 0; i < 4; i++)
		{
			NodeTable[NodeNum].Name[i] = Name[i];
		}
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
				for (int i = 0; i < 4; i++)
				{
					NodeTable[NodeNum].Name[i] = Name[i];
				}
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
bool Graph::insertEdge(string str1, string str2, int cost)
{
	int v1, v2;
	v1 = findV(str1);
	v2 = findV(str2);
	if(v1==-1)
		cout << "������"<<str1<<"��㣡" << endl;
	else if(v2==-1)
		cout << "������" << str2 << "��㣡" << endl;
	else {
		insertEdge(v1, v2, cost);
		return true;
	}
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
	NodeTable[v].Name.clear();
	NodeTable[v].first = NULL;
	NodeTable[v].flag = 0;
}
bool Graph::deleteVertex(string str)
{
	int v = findV(str);
	if (v != -1){
		deleteVertex(v);
		return true;
	}
	else
		cout << "������" << str << "��㣡" << endl;
	return false;
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
bool Graph::deleteEdge(string str1, string str2)		//ɾ��
{
	int v1, v2;
	v1 = findV(str1);
	v2 = findV(str2);
	if (v1 == -1)
		cout << "������" << str1 << "��㣡" << endl;
	else if (v2 == -1)
		cout << "������" << str2 << "��㣡" << endl;
	else {
		deleteEdge(v1, v2);
		return true;
	}
	return false;
}
//��ʼ��
void Graph::Init()
{
	ifstream os;
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
	for (int i = 0; i < NodeNum; i++)
		Dijkstra(i);
}


<<<<<<< HEAD
=======
}

void Graph::Dijkstra(int v)
{
	int Inf = 0x3fffff;						//��ʼ�����ֵ
	int* vis = new int[NodeNum + 1]();		//�Ƿ���ʹ�
	int* dis = new int[NodeNum + 1]();		//Ȩֵ
	int* fa = new int[NodeNum + 1]();		//��һ��
	for (int t = 1; t <= NodeNum; t++)		//�ȳ�ʼ��
		dis[t] = Inf;
	Edge * p = NodeTable[v].first;			//ȡ��ǰ�ڵ���Ϣ�ڽ�
	while (p != NULL)
	{
		dis[p->dest] = p->cost;
		fa[p->dest] = p->dest;
	}
	vis[v] = 1;								//��Ƿ��ʹ�
	for (int t = 1; t < NodeNum; t++)
	{
		int minn = Inf, temp;
		for (int i = 1; i <= NodeNum; i++)
		{
			if (!vis[i] && dis[i] < minn)
			{
				minn = dis[i];
				temp = i;
			}
		}
		vis[temp] = 1;						//���temp���ʹ�
		Edge* p1 = NodeTable[temp].first;	//�ɳڲ���
		while (p1 != NULL)
		{
			if (p1->cost + dis[temp] < dis[p1->dest])
			{
				dis[p1->dest] = p1->cost + dis[temp];
				fa[p1->dest] = fa[temp];	//������һ��
			}
		}
	}
	NodeTable[v].R = new Route[NodeNum];
	for (int i = 1; i <= NodeNum; i++)
	{
		for (int j = 0; j < 4; j++)
			NodeTable[v].R[i].dest[j] = NodeTable[i].Name[j];
		if (i == v)
		{
			NodeTable[v].R[i].next[0] = 127;
			NodeTable[v].R[i].next[1] = 0;
			NodeTable[v].R[i].next[2] = 0;
			NodeTable[v].R[i].next[3] = 1;
			NodeTable[v].R[i].cost = 0;
		}
		else
		{
			for (int j = 0; j < 4; j++)
				NodeTable[v].R[i].next[1] = NodeTable[fa[i]].Name[j];
			NodeTable[v].R[i].cost = dis[i];
		}
	}
}
>>>>>>> dd56904958774f3e52590c13475fb2ba1df59b16
