#include"stdafx.h"
#include"GetTemLib.h"
#include<iostream>
using namespace std;

int main()
{
	GetTemLib gettem;

	gettem.setLibPath("E:/_CODE/GetHistoryTem/TemHistoryLib/TemHistoryLib/temData");


	float tem;
	//gettem.getEstTemp(tem, 4, 0, 30, 20,20,6);
	//cout << tem << endl;
	
	float p[24];
	//gettem.getHistoryTemVec(p, 6, 21, HK_CHANGSHA);

	//for (int i = 0; i < 24; i++)
	//{
	//	cout << p[i] << endl;
	//}

	gettem.getHistoryTemp(tem, 2, 10, 1, 30, 80, 40.0);



	system("pause");
	return 0;
}