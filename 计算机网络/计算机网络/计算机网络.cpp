﻿// 计算机网络.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include "pch.h"
#include"Graph.h"
#include <iostream>

int main()
{
	Graph G;
	cout << "从文件中读取路由信息；" << endl;
	cout << "生成路由表中..." << endl;
	G.Init();
	int chooes;
	while (1)
	{
		cout << "输入收到的链路改变信息" << endl;
		cout << "(1)代表添加一个路由器;" << endl << "(2)代表添加一条链路;" << endl;
		cout << "(3)代表删除一个路由器;" << endl << "(4)代表删除一条链路;" << endl;
		cin >> chooes;
	}
}

