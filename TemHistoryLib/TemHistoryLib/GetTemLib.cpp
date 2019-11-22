#include"stdafx.h"
#include<math.h>
#include"GetTemLib.h"
#include<iostream>
#include <fstream>
#include<sstream>
#include<string>
#include<vector>
using namespace std;




// 获取估计温度
void GetTemLib::getEstTemVec(float p[24],float TempMax, float TempMin, int TimeMax, int TimeMin)
{
	;
	for (int i = 0; i < 24; i++)
	{
		p[i] = 0.5*(TempMax + TempMin) + 0.5*(TempMax - TempMin)*sin( 3.14159 / (TimeMax - TimeMin)*(i - (TimeMax + TimeMin) / 2));
		//cout << p[i] << endl;
	}

}


// 根据经纬度计算两点的距离
double GetTemLib::GetLongDistance(double lon1, double lat1, double lon2, double lat2)
{
	double ew1, ns1, ew2, ns2;

	double distance;

<<<<<<< HEAD

=======
	// 角度转换为弧度

	ew1 = lon1 * DEF_PI180;

	ns1 = lat1 * DEF_PI180;

	ew2 = lon2 * DEF_PI180;

	ns2 = lat2 * DEF_PI180;

	// 求大圆劣弧与球心所夹的角(弧度)

	distance = sin(ns1) * sin(ns2) + cos(ns1) * cos(ns2) * cos(ew1 - ew2);

	// 调整到[-1..1]范围内，避免溢出

	if (distance > 1.0)

		distance = 1.0;

	else if (distance < -1.0)

		distance = -1.0;

	// 求大圆劣弧长度

	distance = DEF_R * acos(distance);

	return distance;
}






>>>>>>> bddcc0a... 淇敼鐩稿簲鐨勫舰寮�
// 获取历史温度曲线
bool GetTemLib::getHistoryTemVec(float p[24], int Month, int Day, int LOCATION)
{
	if (m_libPath == "")
		return false;

	int JD; //积日

	/*求积日*/
	
	for (int i = 0; ; i++)
	{
		if (i == 365)return false; 
		else if (Month == Month_day_JD[i][0] && Day == Month_day_JD[i][1])
		{
			JD = Month_day_JD[i][2];
			break;
		}
	}

	int Line = JD*24-23;//从csv数据中第Line行开始取数据
	//cout << "Line:" << Line << endl;
	
	//以下是读取数据到相应数组
	string FilePath;
	switch (LOCATION) 
	{
	case(HK_HAERBIN):
		FilePath = m_libPath + "/1哈尔滨.csv";
		break;
	case(HK_SHENYANG):
		FilePath = m_libPath + "/2沈阳.csv";
		break;
	case(HK_BEIJING):
		FilePath = m_libPath + "/3北京.csv";
		break;
	case(HK_JINAN):
		FilePath = m_libPath + "/4济南.csv";
		break;
	case(HK_HEFEI):
		FilePath = m_libPath + "/5合肥.csv";
		break;
	case(HK_CHANGSHA):
		FilePath = m_libPath + "/6长沙.csv";
		break;
	case(HK_GUANGZHOU):
		FilePath = m_libPath + "/7广州.csv";
		break;
	case(HK_HAIKOU):
		FilePath = m_libPath + "/8海口.csv";
		break;
	case(HK_DULAN):
		FilePath = m_libPath + "/9都兰.csv";
		break;
	case(HK_WULUMUQI):
		FilePath = m_libPath + "/10乌鲁木齐.csv";
		break;
	
	}
	
	if(!ReadCsvTem(FilePath.c_str(), p, Line))
		return false;
	

	for (int i = 0; i < 24; i++)
	{
		if (p[i] < -200 && i == 0)
		{
			for (int j = 1; j < 24; j++)
			{
				if (p[j] > -200)
					p[i] = p[i - 10];
			}
			continue;
		}

		if (p[i] < -200)
		{
			p[i] = p[i - 1];
			continue;
		}

		

	}

	

	 
	return true;

}

// 获取气温估计值
bool GetTemLib::getEstTemp(float & tem,int hour, int minute, float TempMax, float TempMin, int TimeMax, int TimeMin)
{
	if (hour < 0 || hour>23)
		return false;
	if (minute < 0 || minute>59)
		return false;

	float TemVec[24];
	getEstTemVec(TemVec, TempMax, TempMin, TimeMax, TimeMin);

	if (hour < 23)
	{
		float leftValue = TemVec[hour];
		float rightValue = TemVec[hour + 1];

		tem = leftValue + (float)minute / 60.0*(rightValue - leftValue);
	}

	if (hour == 23)
	{
		float leftValue = TemVec[hour - 1];
		float rightValue = TemVec[hour];

		tem = rightValue + (float)minute / 60.0*(rightValue - leftValue);
	}

	return true;
}

// 设置存放历史数据文件夹路径
void GetTemLib::setLibPath(string libPath)
{
	m_libPath = libPath;
	return;
}






/*……………………ReadCsvTem 读取csv数据*/

bool GetTemLib::ReadCsvTem(const char * FilePath, float get[24], int firstLine)
{
	ifstream file(FilePath);
	if (!file)
		return false;

	string line;
	int lineNum = 0;//标志读到第几行
	int TimeNum = 0;//数组下标
	while(getline(file, line))
	{
		if (lineNum >= firstLine)//到指定位置开始向数组存数据
		{
			istringstream sin(line);
			vector<string> fields; 
			string field;

			while (getline(sin, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
			{

				fields.push_back(field); //将刚刚读取的字符串添加到向量fields中

			}
			if (fields.size() != 8) // 缺失项
			{
				get[TimeNum] = -273.0;
				TimeNum++;
			}
			else
			{
				float tem = atof(fields[5].c_str());
				get[TimeNum] = tem;
				TimeNum++;
			}



		}

		if (lineNum == firstLine + 23)
			return true;

		lineNum++;
	}
	return true;
	
}

int Month_day_JD[365][3] = {
	1	,	1	,	1	,
	1	,	2	,	2	,
	1	,	3	,	3	,
	1	,	4	,	4	,
	1	,	5	,	5	,
	1	,	6	,	6	,
	1	,	7	,	7	,
	1	,	8	,	8	,
	1	,	9	,	9	,
	1	,	10	,	10	,
	1	,	11	,	11	,
	1	,	12	,	12	,
	1	,	13	,	13	,
	1	,	14	,	14	,
	1	,	15	,	15	,
	1	,	16	,	16	,
	1	,	17	,	17	,
	1	,	18	,	18	,
	1	,	19	,	19	,
	1	,	20	,	20	,
	1	,	21	,	21	,
	1	,	22	,	22	,
	1	,	23	,	23	,
	1	,	24	,	24	,
	1	,	25	,	25	,
	1	,	26	,	26	,
	1	,	27	,	27	,
	1	,	28	,	28	,
	1	,	29	,	29	,
	1	,	30	,	30	,
	1	,	31	,	31	,
	2	,	1	,	32	,
	2	,	2	,	33	,
	2	,	3	,	34	,
	2	,	4	,	35	,
	2	,	5	,	36	,
	2	,	6	,	37	,
	2	,	7	,	38	,
	2	,	8	,	39	,
	2	,	9	,	40	,
	2	,	10	,	41	,
	2	,	11	,	42	,
	2	,	12	,	43	,
	2	,	13	,	44	,
	2	,	14	,	45	,
	2	,	15	,	46	,
	2	,	16	,	47	,
	2	,	17	,	48	,
	2	,	18	,	49	,
	2	,	19	,	50	,
	2	,	20	,	51	,
	2	,	21	,	52	,
	2	,	22	,	53	,
	2	,	23	,	54	,
	2	,	24	,	55	,
	2	,	25	,	56	,
	2	,	26	,	57	,
	2	,	27	,	58	,
	2	,	28	,	59	,
	3	,	1	,	60	,
	3	,	2	,	61	,
	3	,	3	,	62	,
	3	,	4	,	63	,
	3	,	5	,	64	,
	3	,	6	,	65	,
	3	,	7	,	66	,
	3	,	8	,	67	,
	3	,	9	,	68	,
	3	,	10	,	69	,
	3	,	11	,	70	,
	3	,	12	,	71	,
	3	,	13	,	72	,
	3	,	14	,	73	,
	3	,	15	,	74	,
	3	,	16	,	75	,
	3	,	17	,	76	,
	3	,	18	,	77	,
	3	,	19	,	78	,
	3	,	20	,	79	,
	3	,	21	,	80	,
	3	,	22	,	81	,
	3	,	23	,	82	,
	3	,	24	,	83	,
	3	,	25	,	84	,
	3	,	26	,	85	,
	3	,	27	,	86	,
	3	,	28	,	87	,
	3	,	29	,	88	,
	3	,	30	,	89	,
	3	,	31	,	90	,
	4	,	1	,	91	,
	4	,	2	,	92	,
	4	,	3	,	93	,
	4	,	4	,	94	,
	4	,	5	,	95	,
	4	,	6	,	96	,
	4	,	7	,	97	,
	4	,	8	,	98	,
	4	,	9	,	99	,
	4	,	10	,	100	,
	4	,	11	,	101	,
	4	,	12	,	102	,
	4	,	13	,	103	,
	4	,	14	,	104	,
	4	,	15	,	105	,
	4	,	16	,	106	,
	4	,	17	,	107	,
	4	,	18	,	108	,
	4	,	19	,	109	,
	4	,	20	,	110	,
	4	,	21	,	111	,
	4	,	22	,	112	,
	4	,	23	,	113	,
	4	,	24	,	114	,
	4	,	25	,	115	,
	4	,	26	,	116	,
	4	,	27	,	117	,
	4	,	28	,	118	,
	4	,	29	,	119	,
	4	,	30	,	120	,
	5	,	1	,	121	,
	5	,	2	,	122	,
	5	,	3	,	123	,
	5	,	4	,	124	,
	5	,	5	,	125	,
	5	,	6	,	126	,
	5	,	7	,	127	,
	5	,	8	,	128	,
	5	,	9	,	129	,
	5	,	10	,	130	,
	5	,	11	,	131	,
	5	,	12	,	132	,
	5	,	13	,	133	,
	5	,	14	,	134	,
	5	,	15	,	135	,
	5	,	16	,	136	,
	5	,	17	,	137	,
	5	,	18	,	138	,
	5	,	19	,	139	,
	5	,	20	,	140	,
	5	,	21	,	141	,
	5	,	22	,	142	,
	5	,	23	,	143	,
	5	,	24	,	144	,
	5	,	25	,	145	,
	5	,	26	,	146	,
	5	,	27	,	147	,
	5	,	28	,	148	,
	5	,	29	,	149	,
	5	,	30	,	150	,
	5	,	31	,	151	,
	6	,	1	,	152	,
	6	,	2	,	153	,
	6	,	3	,	154	,
	6	,	4	,	155	,
	6	,	5	,	156	,
	6	,	6	,	157	,
	6	,	7	,	158	,
	6	,	8	,	159	,
	6	,	9	,	160	,
	6	,	10	,	161	,
	6	,	11	,	162	,
	6	,	12	,	163	,
	6	,	13	,	164	,
	6	,	14	,	165	,
	6	,	15	,	166	,
	6	,	16	,	167	,
	6	,	17	,	168	,
	6	,	18	,	169	,
	6	,	19	,	170	,
	6	,	20	,	171	,
	6	,	21	,	172	,
	6	,	22	,	173	,
	6	,	23	,	174	,
	6	,	24	,	175	,
	6	,	25	,	176	,
	6	,	26	,	177	,
	6	,	27	,	178	,
	6	,	28	,	179	,
	6	,	29	,	180	,
	6	,	30	,	181	,
	7	,	1	,	182	,
	7	,	2	,	183	,
	7	,	3	,	184	,
	7	,	4	,	185	,
	7	,	5	,	186	,
	7	,	6	,	187	,
	7	,	7	,	188	,
	7	,	8	,	189	,
	7	,	9	,	190	,
	7	,	10	,	191	,
	7	,	11	,	192	,
	7	,	12	,	193	,
	7	,	13	,	194	,
	7	,	14	,	195	,
	7	,	15	,	196	,
	7	,	16	,	197	,
	7	,	17	,	198	,
	7	,	18	,	199	,
	7	,	19	,	200	,
	7	,	20	,	201	,
	7	,	21	,	202	,
	7	,	22	,	203	,
	7	,	23	,	204	,
	7	,	24	,	205	,
	7	,	25	,	206	,
	7	,	26	,	207	,
	7	,	27	,	208	,
	7	,	28	,	209	,
	7	,	29	,	210	,
	7	,	30	,	211	,
	7	,	31	,	212	,
	8	,	1	,	213	,
	8	,	2	,	214	,
	8	,	3	,	215	,
	8	,	4	,	216	,
	8	,	5	,	217	,
	8	,	6	,	218	,
	8	,	7	,	219	,
	8	,	8	,	220	,
	8	,	9	,	221	,
	8	,	10	,	222	,
	8	,	11	,	223	,
	8	,	12	,	224	,
	8	,	13	,	225	,
	8	,	14	,	226	,
	8	,	15	,	227	,
	8	,	16	,	228	,
	8	,	17	,	229	,
	8	,	18	,	230	,
	8	,	19	,	231	,
	8	,	20	,	232	,
	8	,	21	,	233	,
	8	,	22	,	234	,
	8	,	23	,	235	,
	8	,	24	,	236	,
	8	,	25	,	237	,
	8	,	26	,	238	,
	8	,	27	,	239	,
	8	,	28	,	240	,
	8	,	29	,	241	,
	8	,	30	,	242	,
	8	,	31	,	243	,
	9	,	1	,	244	,
	9	,	2	,	245	,
	9	,	3	,	246	,
	9	,	4	,	247	,
	9	,	5	,	248	,
	9	,	6	,	249	,
	9	,	7	,	250	,
	9	,	8	,	251	,
	9	,	9	,	252	,
	9	,	10	,	253	,
	9	,	11	,	254	,
	9	,	12	,	255	,
	9	,	13	,	256	,
	9	,	14	,	257	,
	9	,	15	,	258	,
	9	,	16	,	259	,
	9	,	17	,	260	,
	9	,	18	,	261	,
	9	,	19	,	262	,
	9	,	20	,	263	,
	9	,	21	,	264	,
	9	,	22	,	265	,
	9	,	23	,	266	,
	9	,	24	,	267	,
	9	,	25	,	268	,
	9	,	26	,	269	,
	9	,	27	,	270	,
	9	,	28	,	271	,
	9	,	29	,	272	,
	9	,	30	,	273	,
	10	,	1	,	274	,
	10	,	2	,	275	,
	10	,	3	,	276	,
	10	,	4	,	277	,
	10	,	5	,	278	,
	10	,	6	,	279	,
	10	,	7	,	280	,
	10	,	8	,	281	,
	10	,	9	,	282	,
	10	,	10	,	283	,
	10	,	11	,	284	,
	10	,	12	,	285	,
	10	,	13	,	286	,
	10	,	14	,	287	,
	10	,	15	,	288	,
	10	,	16	,	289	,
	10	,	17	,	290	,
	10	,	18	,	291	,
	10	,	19	,	292	,
	10	,	20	,	293	,
	10	,	21	,	294	,
	10	,	22	,	295	,
	10	,	23	,	296	,
	10	,	24	,	297	,
	10	,	25	,	298	,
	10	,	26	,	299	,
	10	,	27	,	300	,
	10	,	28	,	301	,
	10	,	29	,	302	,
	10	,	30	,	303	,
	10	,	31	,	304	,
	11	,	1	,	305	,
	11	,	2	,	306	,
	11	,	3	,	307	,
	11	,	4	,	308	,
	11	,	5	,	309	,
	11	,	6	,	310	,
	11	,	7	,	311	,
	11	,	8	,	312	,
	11	,	9	,	313	,
	11	,	10	,	314	,
	11	,	11	,	315	,
	11	,	12	,	316	,
	11	,	13	,	317	,
	11	,	14	,	318	,
	11	,	15	,	319	,
	11	,	16	,	320	,
	11	,	17	,	321	,
	11	,	18	,	322	,
	11	,	19	,	323	,
	11	,	20	,	324	,
	11	,	21	,	325	,
	11	,	22	,	326	,
	11	,	23	,	327	,
	11	,	24	,	328	,
	11	,	25	,	329	,
	11	,	26	,	330	,
	11	,	27	,	331	,
	11	,	28	,	332	,
	11	,	29	,	333	,
	11	,	30	,	334	,
	12	,	1	,	335	,
	12	,	2	,	336	,
	12	,	3	,	337	,
	12	,	4	,	338	,
	12	,	5	,	339	,
	12	,	6	,	340	,
	12	,	7	,	341	,
	12	,	8	,	342	,
	12	,	9	,	343	,
	12	,	10	,	344	,
	12	,	11	,	345	,
	12	,	12	,	346	,
	12	,	13	,	347	,
	12	,	14	,	348	,
	12	,	15	,	349	,
	12	,	16	,	350	,
	12	,	17	,	351	,
	12	,	18	,	352	,
	12	,	19	,	353	,
	12	,	20	,	354	,
	12	,	21	,	355	,
	12	,	22	,	356	,
	12	,	23	,	357	,
	12	,	24	,	358	,
	12	,	25	,	359	,
	12	,	26	,	360	,
	12	,	27	,	361	,
	12	,	28	,	362	,
	12	,	29	,	363	,
	12	,	30	,	364	,
	12	,	31	,	365

};