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
//���캯��

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
	NodeNum = 0;
}
//�ҵ�
int Graph::findV(int name[])
{
	for (int i = 0; i < NodeNum; i++) 
		for (int j = 0; j < 4; j++) {
			if (NodeTable[i].Name[j] == name[j]){
				if (j == 3) return i;
				else continue;
			}
			else break;
		}
	return -1;
}
//�ӵ�
bool Graph::insertVertex(int Name[])
{
	if (NodeNum < MaxNum)	//˳�����
	{
		for (int i = 0; i < 4; i++){
			NodeTable[NodeNum].Name[i] = Name[i];
		}
		NodeTable[NodeNum].first = NULL;
		NodeNum++;
		return true;
	}
	else 
		cout << "�ڵ��Ѿ����ˣ�" << endl;
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
bool Graph::insertEdge(int str1[], int str2[], int cost)
{
	int v1, v2;
	v1 = findV(str1);
	v2 = findV(str2);
	if(v1==-1)
		cout << "������"<<str1[0]<<'.'<<str1[1]<<'.'<<str1[2]<<'.'<<str1[3]<<"��㣡" << endl;
	else if(v2==-1)
		cout << "������" << str2[0] << '.' << str2[1] << '.' << str2[2] << '.' << str2[3] << "��㣡" << endl;
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
	delete[] NodeTable[v].R;
	NodeTable[v].first = NULL;

	//����Ľڵ�ǰ��
	for(int i=v+1;i<NodeNum;i++){
		NodeTable[i - 1].first = NodeTable[i - 1].first;
		for(int j=0;j<4;j++)
			NodeTable[i - 1].Name[j] = NodeTable[i].Name[j];
		NodeTable[i - 1].R = NodeTable[i].R;
	}
}
bool Graph::deleteVertex(int name[])
{
	int v = findV(name);
	if (v != -1){
		deleteVertex(v);
		return true;
	}
	else
		cout << "������" << name[0] << '.' << name[1] << '.' << name[2] << '.' << name[3] << "��㣡" << endl;
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
bool Graph::deleteEdge(int str1[], int str2[])		//ɾ��
{
	int v1, v2;
	v1 = findV(str1);
	v2 = findV(str2);
	if (v1 == -1)
		cout << "������" << str1[0] << '.' << str1[1] << '.' << str1[2] << '.' << str1[3] << "��㣡" << endl;
	else if (v2 == -1)
		cout << "������" << str1[0] << '.' << str1[1] << '.' << str1[2] << '.' << str1[3] << "��㣡" << endl;
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
	os >> v >> e;
	int cost;
	int str1[4],str2[4];
	for (int i = 0; i < v; i++)
	{
		os >> str1[0]>>str1[1]>>str1[2]>>str1[3];
		insertVertex(str1);
	}
	for (int i = 0; i < e; i++)
	{
		os >>  str1[0] >> str1[1] >> str1[2] >> str1[3] >> str2[0] >> str2[1] >> str2[2] >> str2[3] >> cost;
		insertEdge(str1, str2, cost);
	}
	for (int i = 0; i < NodeNum; i++)
		Dijkstra(i);
}

void Graph::Dijkstra(int v)
{
	int* vis = new int[NodeNum + 1];		//�Ƿ���ʹ�
	int* dis = new int[NodeNum + 1];		//Ȩֵ
	int* fa = new int[NodeNum + 1];			//��һ��
	for (int t = 0; t < NodeNum; t++)		//�ȳ�ʼ��
		dis[t] = Inf;
	dis[v] = 0;
	for (int t = 0;t < NodeNum; t++)
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
		int minn = Inf, temp= NodeNum + 1;
		for (int i = 0; i < NodeNum; i++)
		{
			if (!vis[i] && dis[i] < minn)
			{
				minn = dis[i];
				temp = i;
			}
		}
		if (temp = NodeNum + 1)
			break;
		vis[temp] = 1;						//���temp���ʹ�
		Edge* p1 = NodeTable[temp].first;	//�ɳڲ���
		while(p1 != NULL)
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
	for(int i = 0; i < NodeNum; i++)
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

void Graph::Update()
{
	for (int i = 0; i < NodeNum; i++)
	{
		Dijkstra(i);
	}
}