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

//析构函数
Graph::~Graph()
{
	clear();
}
//清空图
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
//找点
int Graph::findV(string str)
{
	for (int i = 0; i < NodeNum; i++)
		if (NodeTable[i].Name == str)
			return i;
	return -1;
}
//加点
bool Graph::insertVertex(string Name)
{
	if (NodeNum < MaxNum)	//顺序添加
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
//加边
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
bool Graph::insertEdge(string str1, string str2, int cost)
{
	int v1, v2;
	v1 = findV(str1);
	v2 = findV(str2);
	if(v1==-1)
		cout << "不存在"<<str1<<"这点！" << endl;
	else if(v2==-1)
		cout << "不存在" << str2 << "这点！" << endl;
	else {
		insertEdge(v1, v2, cost);
		return true;
	}
	return false;
}

//删点
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
				last = temp;
				temp = temp->next;
			}	
			last = temp = NULL;
		}
			//删除当前节点里的这条边
		temp = current;
		current = current->next;
		delete temp;
	}
	temp = NULL;

	//删除点
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
		cout << "不存在" << str << "这点！" << endl;
	return false;
}
//删边
void Graph::deleteEdge(int v1, int v2)		//删边
{
	Edge* current, *last;
	//在v1中删除v2
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
	//在v1中删除v1
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
bool Graph::deleteEdge(string str1, string str2)		//删边
{
	int v1, v2;
	v1 = findV(str1);
	v2 = findV(str2);
	if (v1 == -1)
		cout << "不存在" << str1 << "这点！" << endl;
	else if (v2 == -1)
		cout << "不存在" << str2 << "这点！" << endl;
	else {
		deleteEdge(v1, v2);
		return true;
	}
	return false;
}
//初始化
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


