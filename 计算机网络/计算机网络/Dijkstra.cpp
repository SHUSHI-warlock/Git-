#include"pch.h"
#include"Graph.h"
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<cstring>
#include <algorithm>
#include <iostream>
#include<string>
#include<stack>
#include<queue>
#include<fstream>
using namespace std;
//更新
void Graph::Update()
{
	for (int i = 0; i < NodeNum; i++)
	{
		if (NodeTable[i].flag == 1) {
			delete[] NodeTable[i].R;
			Dijkstra(i);
		}
	}
}
//生成路由表
void Graph::Dijkstra(int v)
{
	int* vis = new int[NodeNum + 1];		//是否访问过
	int* dis = new int[NodeNum + 1];		//权值
	int* fa = new int[NodeNum + 1];			//下一跳
	for (int t = 0; t < NodeNum; t++)		//先初始化
		dis[t] = Inf;
	dis[v] = 0;
	for (int t = 0; t < NodeNum; t++)
		vis[t] = 0;
	Edge * p = NodeTable[v].first;			//取当前节点信息邻接
	while (p != NULL)
	{
		dis[p->dest] = p->cost;
		fa[p->dest] = p->dest;
		p = p->next;			//之前少了
	}
	vis[v] = 1;								//标记访问过
	for (int t = 1; t < NodeNum; t++)
	{
		int minn = Inf, temp = MaxNum + 1;
		for (int i = 0; i < NodeNum; i++)
		{
			if ((!vis[i]) && dis[i] < minn)
			{
				minn = dis[i];
				temp = i;
			}
		}
		if (temp == MaxNum + 1)
			break;
		vis[temp] = 1;						//标记temp访问过
		Edge* p1 = NodeTable[temp].first;	//松弛操作
		while (p1 != NULL)
		{
			if (p1->cost + dis[temp] < dis[p1->dest])
			{
				dis[p1->dest] = p1->cost + dis[temp];
				fa[p1->dest] = fa[temp];	//更新下一跳
			}
			p1 = p1->next;
		}
	}
	NodeTable[v].R = new Route[NodeNum];
	for (int i = 0; i < NodeNum; i++)
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
			if (dis[i] != Inf)
				for (int j = 0; j < 4; j++)
					NodeTable[v].R[i].next[j] = NodeTable[fa[i]].Name[j];
			NodeTable[v].R[i].cost = dis[i];
		}
	}
	delete[] vis;
	delete[] dis;
	delete[] fa;
}

void Graph::Print()
{
	int n[4];
	for (int i = 0; i < NodeNum; i++)
	{
		if (NodeTable[i].flag == 0)
			continue;
		for (int j = 0; j < 4; j++)
		{
			n[j] = NodeTable[i].Name[j];
		}
		Print(n);
	}
}

void Graph::Print(int name[])
{
	int n = findV(name);
	if (n == -1)
		cout << "IP错误，无法找到的IP" << endl;
	else
	{
		cout << "|￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣|" << endl;
		cout << "|				" << setiosflags(ios::left) << setw(3) << name[0] << '.';
		cout << setiosflags(ios::left) << setw(3) << name[1] << '.';
		cout << setiosflags(ios::left) << setw(3) << name[2] << '.';
		cout << setiosflags(ios::left) << setw(3) << name[3] << "的路由表     " << "				 |" << endl;
		cout << "|________________________________________________________________________________________|" << endl;
		cout << "|	Destination				Gateway				Cost	 |" << endl;
		for (int j = 0; j < NodeNum; j++) {
			if (NodeTable[j].flag == 0)
				continue;
			if (NodeTable[n].R[j].cost == Inf) {
				cout << "|\t\t\t\t" << setiosflags(ios::left) << setw(3) << NodeTable[n].R[j].dest[0] << '.';
				cout << setiosflags(ios::left) << setw(3) << NodeTable[n].R[j].dest[1] << '.';
				cout << setiosflags(ios::left) << setw(3) << NodeTable[n].R[j].dest[2] << '.';
				cout << setiosflags(ios::left) << setw(3) << NodeTable[n].R[j].dest[3] << "的网络不可达！\t\t\t\t |" << endl;
			}
			else {
				cout << "|	" << setiosflags(ios::left) << setw(3) << NodeTable[n].R[j].dest[0] << '.';
				cout << setiosflags(ios::left) << setw(3) << NodeTable[n].R[j].dest[1] << '.';
				cout << setiosflags(ios::left) << setw(3) << NodeTable[n].R[j].dest[2] << '.';
				cout << setiosflags(ios::left) << setw(3) << NodeTable[n].R[j].dest[3] << "\t\t\t\t";
				cout << setiosflags(ios::left) << setw(3) << NodeTable[n].R[j].next[0] << '.';
				cout << setiosflags(ios::left) << setw(3) << NodeTable[n].R[j].next[1] << '.';
				cout << setiosflags(ios::left) << setw(3) << NodeTable[n].R[j].next[2] << '.';
				cout << setiosflags(ios::left) << setw(3) << NodeTable[n].R[j].next[3] << "\t\t\t";
				cout << NodeTable[n].R[j].cost << "	 |" << endl;
			}
			//printf("%d.%d.%d.%d\t%d.%d.%d.%d\t%d\n",  NodeTable[n].R->next[0], NodeTable[n].R->next[1], NodeTable[n].R->next[2], NodeTable[n].R->next[3], NodeTable[n].R->cost);
		}
		cout << "|________________________________________________________________________________________|" << endl << endl;
	}
}