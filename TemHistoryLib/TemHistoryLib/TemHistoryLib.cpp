// TemHistoryLib.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include"GetTemLib.h"
using namespace std;
int main()
{
	float a[24];
    GetTemLib tem;



	
	bool m = tem.getHistoryTemp(a, 8,29,BEIJING);
	if (m)
	{
		for (int i = 0; i < 24; i++)
		{
			cout << a[i] << endl;
		}
	}
		cout << "m:" << m << endl;
	
	return 0;

}

