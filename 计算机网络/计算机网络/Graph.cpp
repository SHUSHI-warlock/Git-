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
	queue<int>q;
	node[q].
}