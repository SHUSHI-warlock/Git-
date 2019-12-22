// 计算机网络.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include "pch.h"
#include"Graph.h"
#include <iostream>
#include<iomanip>

void MainTable(int &c)
{
	cout << "\t\t\t\t" << "╔═════════════════════════════════════════════════╗" << endl;
	cout << "\t\t\t\t" << "║                   路由生成程序		  ║" << endl;
	cout << "\t\t\t\t" << "╠════════════════════════╦════════════════════════╣" << endl;
	cout << "\t\t\t\t" << "║ ① 添加节点      	 ║ ② 添加链路            ║" << endl;
	cout << "\t\t\t\t" << "╠════════════════════════╬════════════════════════╣" << endl;
	cout << "\t\t\t\t" << "║ ③ 删除节点      	 ║ ④ 删除链路		  ║" << endl;
	cout << "\t\t\t\t" << "╠════════════════════════╬════════════════════════╣" << endl;
	cout << "\t\t\t\t" << "║ ⑤ 查看路由        	 ║ ⑥ 退出		  ║" << endl;
	cout << "\t\t\t\t" << "╚════════════════════════╩════════════════════════╝" << endl;
	cout << "\t\t\t\t" << "请输入：";
	cin >> c;
	while (c < 1 || c>6) {
		cout << "输入有误！请重新输入！" << endl;
		cin >> c;
	}
	system("cls");
}

int main()
{
	Graph G;
	/*cout << "从文件中读取路由信息；" << endl;
	cout << "生成路由表中..." << endl;*/
	G.Init();
	int chooes=-1;
	int IP[4],IP2[4],cost;
	while (chooes!=0)
	{
		MainTable(chooes);
		switch (chooes)
		{
		case 1:
			cout << "请输入一个路由器IP地址：" << endl;
			cin >> IP[0]>> IP[1] >> IP[2] >> IP[3];
			//加检测
			G.insertVertex(IP);
			break;
		case 2:
			cout << "请输入一端的路由器IP地址：" << endl;
			cin >> IP[0] >> IP[1] >> IP[2] >> IP[3];
			cout << "请输入另一端的路由器IP地址：" << endl;
			cin >> IP2[0] >> IP2[1] >> IP2[2] >> IP2[3];
			cout << "请输入链路的长度：" << endl;
			cin >> cost;
			if (G.insertEdge(IP, IP2, cost)) {
				G.Update();
				cout << "加边成功！" << endl;
			}
			else
				cout << "加边失败！" << endl;
			break;
		case 3:
			cout << "请输入要删除的路由器IP地址：" << endl;
			cin >> IP[0] >> IP[1] >> IP[2] >> IP[3];
			//加检测
			if (G.deleteVertex(IP)) {
				cout << "删点成功" << endl;
				G.Update();
			}
			else
				cout << "删点失败！" << endl;
			break;
		case 4: 
			cout << "请输入删除的一端的路由器IP地址：" << endl;
			cin >> IP[0] >> IP[1] >> IP[2] >> IP[3];
			cout << "请输入另一端的路由器IP地址：" << endl;
			cin >> IP2[0] >> IP2[1] >> IP2[2] >> IP2[3];
			if (G.deleteEdge(IP, IP2)) {
				G.Update();
				cout << "删边成功！" << endl;
			}
			else
				cout << "删边失败！" << endl;
			break;
		case 5:int ways;
			cout << endl << endl << endl;
			cout << "\t\t\t\t" << "╔═════════════════════════════════════════════════╗" << endl;
			cout << "\t\t\t\t" << "║             1）查看所有路由器的路由表		  ║" << endl;
			cout << "\t\t\t\t" << "╠═════════════════════════════════════════════════╣" << endl;
			cout << "\t\t\t\t" << "║             2）查看指定路由器的路由表		  ║" << endl;
			cout << "\t\t\t\t" << "╚═════════════════════════════════════════════════╝" << endl;
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
		system("pause");
		system("cls");
		cin.clear();
	}
	return 0;
}


