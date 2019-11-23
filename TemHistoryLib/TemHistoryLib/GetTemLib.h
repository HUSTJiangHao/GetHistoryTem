#pragma once
#include"stdafx.h"
#include<string>

#define HK_HAERBIN   1
#define HK_SHENYANG  2
#define HK_BEIJING   3
#define HK_JINAN     4
#define HK_HEFEI     5
#define HK_CHANGSHA  6
#define HK_GUANGZHOU 7
#define HK_HAIKOU    8
#define HK_DULAN     9
#define HK_WULUMUQI  10


//#ifdef IRGIS_TEMPHIST
//#define IRGIS_TEMPHIST_API  _declspec(dllexport)
//#else
//#define IRGIS_TEMPHIST_API  _declspec(dllimport)
//#endif  






const double DEF_PI = 3.14159265359; // PI

const double DEF_2PI = 6.28318530712; // 2*PI

const double DEF_PI180 = 0.01745329252; // PI/180.0

const double DEF_R = 6370693.5; // radius of earth



class GetTemLib
{



public:

	GetTemLib() { m_libPath = ""; };

	/*��������getEstTemp��������*/
	// tem ����õ����¶�
	// hour �趨Сʱ
	// minute �趨����
	// TempMax �����
	// TempMin �����
	// TimeMax �����ʱ��
	// TimeMin �����ʱ��
	bool getEstTemp(float &tem,int hour, int minute, float TempMax, float TempMin, int TimeMax = 14, int TimeMin = 5);




	// ���ô����ʷ���ݵ��ļ��е�·��
	void setLibPath(std::string libPath);


	/* ������������ getHistoryTemp ��ȡ��ʷ�¶ȡ�������*/
	// tem :  �¶�
	// month day hour minute �� �� �� ʱ ��
	// Lon ������
	// Lat : γ��
	bool getHistoryTemp(float &tem, int month, int day, int hour, int minute, float Lon, float Lat);



///////////////////////////////////////////////////////////////////
private:

	std::string m_libPath;  // �洢�¶ȼ�¼���ļ���·��


	/*����������������ReadCsvTem ��ȡcsv����*/
	//���� File Path ���ļ�·��
	//���� get       ��������ݵ�����
	//���� firstLine ��csv��ʼ�ڼ���
	//����ֵ         ���Ƿ��ȡ�ɹ�
	//˵���� ������Ϊ -273 ����û�м�¼
	bool ReadCsvTem(const char* FilePath, float get[24], int firstLine);





	/*��������getEstTemVec ��ȡԤ��ʱ�����ߵĺ�����������*/
//���� TempMax TempMin ������һ���¶������Сֵ
//���� TimeMax TimeMin ������һ���¶������Сֵ���ֵ�ʱ�� ��һ��TimeMaxΪ15���ң�TimeMinΪ5��ҵ��
//�����һ������Ϊ24�����飬��ʾ�¶ȴ�С
	void getEstTemVec(float p[24], float TempMax, float TempMin, int TimeMax, int TimeMin);





	/*����������GetLongDistance���ݾ�γ�ȼ���λ�þ��롭����*/
	//lon1 �ص�1�ľ���
	//lat1 �ص�1��γ��
	//lon2 �ص�2�ľ���
	//lat2 �ص�2��γ��
	double GetLongDistance(double lon1, double lat1, double lon2, double lat2);
	



	/*����������������getHistoryTemVec ��ȡĳ��ĳ�յ�24Сʱ���¶����ߡ�������*/
//���� p        �����24Сʱ�¶ȵ�����
//���� Month    ���·�
//���� Day      ������
//���� LOCATION ����������
//����ֵ        �������Ƿ��ѯ��
/*  ������������(�Ѿ�define��) HK_
	 HAERBIN   1  ������
	 SHENYANG  2  ����
	 BEIJING   3  ����
	 JINAN     4  ����
	 HEFEI     5  �Ϸ�
	 CHANGSHA  6  ��ɳ
	 GUANGZHOU 7  ����
	 HAIKOU    8  ����
	 DULAN     9  ����
	 WULUMUQI  10 ��³ľ��*/
	bool getHistoryTemVec(float p[24], int Month, int Day, int LOCATION);



};

/*���ںͻ��ն�Ӧ����*/
extern  int Month_day_JD[][3];