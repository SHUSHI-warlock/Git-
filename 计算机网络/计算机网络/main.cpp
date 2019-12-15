// 计算机网络.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include "pch.h"
#include"Graph.h"
#include <iostream>

int main()
{
	Graph G;
	cout << "从文件中读取路由信息；" << endl;
	cout << "生成路由表中..." << endl;
	G.Init();
	int chooes=-1;
	int IP[4],IP2[4],cost;
	while (chooes!=0)
	{
		cout << "输入收到的链路改变信息（退出请按0）：" << endl;
		cout << "(1)代表添加一个路由器;" << endl << "(2)代表添加一条链路;" << endl;
		cout << "(3)代表删除一个路由器;" << endl << "(4)代表删除一条链路;" << endl;
		cout<< "(5)查看路由表;" << endl;
		cin >> chooes;
		switch (chooes)
		{
		case 1:
			cout << "请输入一个路由器IP地址：" << endl;
			cin >> IP[0]>> IP[1] >> IP[2] >> IP[3];
			//加检测
			G.insertVertex(IP);
			break;
		case 2:
			cout << "请输入一个路由器IP地址：" << endl;
			cin >> IP[0] >> IP[1] >> IP[2] >> IP[3];
			cout << "请输入另一个路由器IP地址：" << endl;
			cin >> IP2[0] >> IP2[1] >> IP2[2] >> IP2[3];
			cout << "请输入链路的长度：" << endl;
			cin >> cost;
			G.insertEdge(IP, IP2, cost);
			G.Update();
			break;
		case 3:
			cout << "请输入要删除的路由器IP地址：" << endl;
			cin >> IP[0] >> IP[1] >> IP[2] >> IP[3];
			//加检测
			G.deleteVertex(IP);
			G.Update();
			break;
		case 4: 
			cout << "请输入要删除的路由器IP地址：" << endl;
			cin >> IP[0] >> IP[1] >> IP[2] >> IP[3];
			cout << "请输入另一个要删除的路由器IP地址：" << endl;
			cin >> IP2[0] >> IP2[1] >> IP2[2] >> IP2[3];
			G.deleteEdge(IP, IP2);
			G.Update();
			break;
		case 5:int ways;
			cout << "1）查看所有路由器的路由表;" << endl << "2）查看指定路由器的路由表:";
			cin >> ways;
			if (ways == 1)
				G.Print();
			else
			{
				cout << "请输入要查看的路由器的IP地址:";
				cin >> IP[0] >> IP[1] >> IP[2] >> IP[3];
				G.Print(IP);
			}
			break;
		default:cout << "即将退出" << endl;
			break;
		}
	}
}

