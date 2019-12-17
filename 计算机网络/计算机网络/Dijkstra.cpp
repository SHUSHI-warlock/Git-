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
//����
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
//����·�ɱ�
void Graph::Dijkstra(int v)
{
	int* vis = new int[NodeNum + 1];		//�Ƿ���ʹ�
	int* dis = new int[NodeNum + 1];		//Ȩֵ
	int* fa = new int[NodeNum + 1];			//��һ��
	for (int t = 0; t < NodeNum; t++)		//�ȳ�ʼ��
		dis[t] = Inf;
	dis[v] = 0;
	for (int t = 0; t < NodeNum; t++)
		vis[t] = 0;
	Edge * p = NodeTable[v].first;			//ȡ��ǰ�ڵ���Ϣ�ڽ�
	while (p != NULL)
	{
		dis[p->dest] = p->cost;
		fa[p->dest] = p->dest;
		p = p->next;			//֮ǰ����
	}
	vis[v] = 1;								//��Ƿ��ʹ�
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
		vis[temp] = 1;						//���temp���ʹ�
		Edge* p1 = NodeTable[temp].first;	//�ɳڲ���
		while (p1 != NULL)
		{
			if (p1->cost + dis[temp] < dis[p1->dest])
			{
				dis[p1->dest] = p1->cost + dis[temp];
				fa[p1->dest] = fa[temp];	//������һ��
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
		cout << "IP�����޷��ҵ���IP" << endl;
	else
	{
		cout << "|����������������������������������������������������������������������������������������|" << endl;
		cout << "|				" << setiosflags(ios::left) << setw(3) << name[0] << '.';
		cout << setiosflags(ios::left) << setw(3) << name[1] << '.';
		cout << setiosflags(ios::left) << setw(3) << name[2] << '.';
		cout << setiosflags(ios::left) << setw(3) << name[3] << "��·�ɱ�     " << "				 |" << endl;
		cout << "|________________________________________________________________________________________|" << endl;
		cout << "|	Destination				Gateway				Cost	 |" << endl;
		for (int j = 0; j < NodeNum; j++) {
			if (NodeTable[j].flag == 0)
				continue;
			if (NodeTable[n].R[j].cost == Inf) {
				cout << "|\t\t\t\t" << setiosflags(ios::left) << setw(3) << NodeTable[n].R[j].dest[0] << '.';
				cout << setiosflags(ios::left) << setw(3) << NodeTable[n].R[j].dest[1] << '.';
				cout << setiosflags(ios::left) << setw(3) << NodeTable[n].R[j].dest[2] << '.';
				cout << setiosflags(ios::left) << setw(3) << NodeTable[n].R[j].dest[3] << "�����粻�ɴ\t\t\t\t |" << endl;
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