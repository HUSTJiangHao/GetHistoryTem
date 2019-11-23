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

	/*…………getEstTemp…………*/
	// tem 计算得到的温度
	// hour 设定小时
	// minute 设定分钟
	// TempMax 最高温
	// TempMin 最低温
	// TimeMax 最高温时间
	// TimeMin 最低温时间
	bool getEstTemp(float &tem,int hour, int minute, float TempMax, float TempMin, int TimeMax = 14, int TimeMin = 5);




	// 设置存放历史数据的文件夹的路径
	void setLibPath(std::string libPath);


	/* ……………… getHistoryTemp 获取历史温度…………*/
	// tem :  温度
	// month day hour minute ： 月 日 时 分
	// Lon ：经度
	// Lat : 纬度
	bool getHistoryTemp(float &tem, int month, int day, int hour, int minute, float Lon, float Lat);



///////////////////////////////////////////////////////////////////
private:

	std::string m_libPath;  // 存储温度记录的文件夹路径


	/*……………………ReadCsvTem 读取csv数据*/
	//参数 File Path ：文件路径
	//参数 get       ：存放数据的数组
	//参数 firstLine ：csv起始第几行
	//返回值         ：是否读取成功
	//说明： 当数据为 -273 表明没有记录
	bool ReadCsvTem(const char* FilePath, float get[24], int firstLine);





	/*…………getEstTemVec 获取预测时间曲线的函数…………*/
//参数 TempMax TempMin ：输入一日温度最大最小值
//参数 TimeMax TimeMin ：输入一日温度最大最小值出现的时间 （一般TimeMax为15左右，TimeMin为5作业）
//输出：一个长度为24的数组，表示温度大小
	void getEstTemVec(float p[24], float TempMax, float TempMin, int TimeMax, int TimeMin);





	/*……………GetLongDistance根据经纬度计算位置距离………*/
	//lon1 地点1的经度
	//lat1 地点1的纬度
	//lon2 地点2的经度
	//lat2 地点2的纬度
	double GetLongDistance(double lon1, double lat1, double lon2, double lat2);
	



	/*……………………getHistoryTemVec 获取某月某日的24小时的温度曲线…………*/
//参数 p        ：存放24小时温度的数组
//参数 Month    ：月份
//参数 Day      ：日期
//参数 LOCATION ：地区代号
//返回值        ：返回是否查询到
/*  地区代号如下(已经define过) HK_
	 HAERBIN   1  哈尔滨
	 SHENYANG  2  沈阳
	 BEIJING   3  北京
	 JINAN     4  济南
	 HEFEI     5  合肥
	 CHANGSHA  6  长沙
	 GUANGZHOU 7  广州
	 HAIKOU    8  海口
	 DULAN     9  都兰
	 WULUMUQI  10 乌鲁木齐*/
	bool getHistoryTemVec(float p[24], int Month, int Day, int LOCATION);



};

/*日期和积日对应数组*/
extern  int Month_day_JD[][3];