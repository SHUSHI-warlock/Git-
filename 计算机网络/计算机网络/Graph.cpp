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

using namespace std;

Graph::~Graph()
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
}
Graph::clear()
{

}

void Graph::insertVertex(string Name)
{
		
	NodeNum++;
}

void Graph::insertEdge(int v1, int v2, int cost)
{
	Edge*current;
	current = NodeTable[v1].first;
	NodeTable[v1].first = new Edge(v2, cost);
	NodeTable[v1].first->next = current;

	current = NodeTable[v2].first;
	NodeTable[v2].first = new Edge(v1, cost);
	NodeTable[v2].first->next = current;
}
