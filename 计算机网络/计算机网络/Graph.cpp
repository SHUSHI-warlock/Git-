#include"pch.h"
#include"Graph.h"

#include<stdio.h>
#include<string>
#include<math.h>
#include <iostream>
#include <algorithm>
#include<cstring>
#include<stack>
#include<queue>


Graph::~Graph()
{
	clear();
}

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
bool Graph::insertVertex(int Name[])
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
			}	
			last = temp = NULL;
		}
			//ɾ����ǰ�ڵ����������
		temp = current;
		current = current->next;
		delete temp;
		temp = NULL;
	}
	//ɾ����
}

void Graph::deleteEdge(int v1, int v2)		//ɾ��
{

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