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
		if(NodeTable[i].flag)
			for (int j = 0; j < 4; j++) {
				if (NodeTable[i].Name[j] == name[j]) {
					if (j == 3)
						return i;
					else continue;
				}
				else break;
			}
	return -1;
}
//�ӵ�
bool Graph::insertVertex(int Name[])
{
	if (findV(Name) != -1) {
		cout << "Ҫ��ӵĵ��Ѵ��ڣ�" << endl;
		return false;
	}
	if (NodeNum < MaxNum)	//˳�����
	{
		for (int i = 0; i < 4; i++){
			NodeTable[NodeNum].Name[i] = Name[i];
		}
		NodeTable[NodeNum].flag = 1;
		NodeTable[NodeNum].first = NULL;
		NodeNum++;
		return true;
	}
	else {
		for (int i = 0; i < MaxNum; i++)
		{
			if(NodeTable[i].flag==0)
			{
				for (int i = 0; i < 4; i++) {
					NodeTable[NodeNum].Name[i] = Name[i];
				}
				NodeTable[NodeNum].flag = 1;
				NodeTable[NodeNum].first = NULL;
				return true;
			}
		}
	}
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
	NodeTable[v].first = NULL;
	delete[] NodeTable[v].R;
	NodeTable[v].flag = 0;
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


