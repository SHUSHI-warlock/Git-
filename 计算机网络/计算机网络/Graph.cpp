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
	//释放节点和边
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
	if (NodeNum < MaxNum)	//顺序添加
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
	NodeTable[v1].first = new Edge(v2, cost);	//首插法
	NodeTable[v1].first->next = current;

	current = NodeTable[v2].first;
	NodeTable[v2].first = new Edge(v1, cost);
	NodeTable[v2].first->next = current;
}

void Graph::deleteVertex(int v)				//删点
{
	//删除该点和其他点的边的信息
	Edge* current,*temp,*last;
	current = NodeTable[v].first;
	while (current!=NULL)
	{
			//删除这条边上另一个节点中的这条边
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
			//删除当前节点里的这条边
		temp = current;
		current = current->next;
		delete temp;
		temp = NULL;
	}
	//删除点
}

void Graph::deleteEdge(int v1, int v2)		//删边
{

}

void Graph::Dijkstra(int v)
{
	int Inf = 0x3fffff;						//初始化最大值
	int* vis = new int[NodeNum + 1]();		//是否访问过
	int* dis = new int[NodeNum + 1]();		//权值
	int* fa = new int[NodeNum + 1]();		//下一跳
	for (int t = 1; t <= NodeNum; t++)		//先初始化
		dis[t] = Inf;
	Edge * p = NodeTable[v].first;			//取当前节点信息邻接
	while (p != NULL)
	{
		dis[p->dest] = p->cost;
		fa[p->dest] = p->dest;
	}
	vis[v] = 1;								//标记访问过
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
		vis[temp] = 1;						//标记temp访问过
		Edge* p1 = NodeTable[temp].first;	//松弛操作
		while (p1 != NULL)
		{
			if (p1->cost + dis[temp] < dis[p1->dest])
			{
				dis[p1->dest] = p1->cost + dis[temp];
				fa[p1->dest] = fa[temp];	//更新下一跳
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