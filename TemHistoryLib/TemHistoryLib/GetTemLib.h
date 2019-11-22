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


#ifdef IRGIS_TEMPHIST
#define IRGIS_TEMPHIST_API  _declspec(dllexport)
#else
#define IRGIS_TEMPHIST_API  _declspec(dllimport)
#endif  



<<<<<<< HEAD
	/*¡­¡­¡­¡­getEstTemp¡­¡­¡­¡­*/
	// tem ¼ÆËãµÃµ½µÄÎÂ¶È
	// hour Éè¶¨Ğ¡Ê±
	// minute Éè¶¨·ÖÖÓ
	// TempMax ×î¸ßÎÂ
	// TempMin ×îµÍÎÂ
	// TimeMax ×î¸ßÎÂÊ±¼ä
	// TimeMin ×îµÍÎÂÊ±¼ä
	bool getEstTemp(float &tem,int hour, int minute, float TempMax, float TempMin, int TimeMax = 14, int TimeMin = 5);
=======
const double DEF_PI = 3.14159265359; // PI
>>>>>>> bddcc0a... ä¿®æ”¹ç›¸åº”çš„å½¢å¼

const double DEF_2PI = 6.28318530712; // 2*PI

const double DEF_PI180 = 0.01745329252; // PI/180.0

<<<<<<< HEAD
=======
const double DEF_R = 6370693.5; // radius of earth



class GetTemLib
{



public:

	GetTemLib() { m_libPath = ""; };

	/*¡­¡­¡­¡­getEstTemp¡­¡­¡­¡­*/
	// tem ¼ÆËãµÃµ½µÄÎÂ¶È
	// hour Éè¶¨Ğ¡Ê±
	// minute Éè¶¨·ÖÖÓ
	// TempMax ×î¸ßÎÂ
	// TempMin ×îµÍÎÂ
	// TimeMax ×î¸ßÎÂÊ±¼ä
	// TimeMin ×îµÍÎÂÊ±¼ä
	bool getEstTemp(float &tem,int hour, int minute, float TempMax, float TempMin, int TimeMax = 14, int TimeMin = 5);



>>>>>>> bddcc0a... ä¿®æ”¹ç›¸åº”çš„å½¢å¼
	// ÉèÖÃ´æ·ÅÀúÊ·Êı¾İµÄÎÄ¼ş¼ĞµÄÂ·¾¶
	void setLibPath(std::string libPath);


	/* ¡­¡­¡­¡­¡­¡­ getHistoryTemp »ñÈ¡ÀúÊ·ÎÂ¶È¡­¡­¡­¡­*/
	// tem :  ÎÂ¶È
	// month day hour minute £º ÔÂ ÈÕ Ê± ·Ö
	// Lon £º¾­¶È
	// Lat : Î³¶È
	bool getHistoryTemp(float &tem, int month, int day, int hour, int minute, float Lon, float Lat);




private:

	std::string m_libPath;  // ´æ´¢ÎÂ¶È¼ÇÂ¼µÄÎÄ¼ş¼ĞÂ·¾¶


	/*¡­¡­¡­¡­¡­¡­¡­¡­ReadCsvTem ¶ÁÈ¡csvÊı¾İ*/
	//²ÎÊı File Path £ºÎÄ¼şÂ·¾¶
	//²ÎÊı get       £º´æ·ÅÊı¾İµÄÊı×é
	//²ÎÊı firstLine £ºcsvÆğÊ¼µÚ¼¸ĞĞ
	//·µ»ØÖµ         £ºÊÇ·ñ¶ÁÈ¡³É¹¦
	//ËµÃ÷£º µ±Êı¾İÎª -273 ±íÃ÷Ã»ÓĞ¼ÇÂ¼
	bool ReadCsvTem(const char* FilePath, float get[24], int firstLine);


<<<<<<< HEAD
=======
	


	/*¡­¡­¡­¡­getEstTemVec »ñÈ¡Ô¤²âÊ±¼äÇúÏßµÄº¯Êı¡­¡­¡­¡­*/
//²ÎÊı TempMax TempMin £ºÊäÈëÒ»ÈÕÎÂ¶È×î´ó×îĞ¡Öµ
//²ÎÊı TimeMax TimeMin £ºÊäÈëÒ»ÈÕÎÂ¶È×î´ó×îĞ¡Öµ³öÏÖµÄÊ±¼ä £¨Ò»°ãTimeMaxÎª15×óÓÒ£¬TimeMinÎª5×÷Òµ£©
//Êä³ö£ºÒ»¸ö³¤¶ÈÎª24µÄÊı×é£¬±íÊ¾ÎÂ¶È´óĞ¡
	void getEstTemVec(float p[24], float TempMax, float TempMin, int TimeMax, int TimeMin);




	



	/*¡­¡­¡­¡­¡­GetLongDistance¸ù¾İ¾­Î³¶È¼ÆËãÎ»ÖÃ¾àÀë¡­¡­¡­*/
	//lon1 µØµã1µÄ¾­¶È
	//lat1 µØµã1µÄÎ³¶È
	//lon2 µØµã2µÄ¾­¶È
	//lat2 µØµã2µÄÎ³¶È
	double GetLongDistance(double lon1, double lat1, double lon2, double lat2);
	


>>>>>>> bddcc0a... ä¿®æ”¹ç›¸åº”çš„å½¢å¼
	/*¡­¡­¡­¡­¡­¡­¡­¡­getHistoryTemVec »ñÈ¡Ä³ÔÂÄ³ÈÕµÄ24Ğ¡Ê±µÄÎÂ¶ÈÇúÏß¡­¡­¡­¡­*/
//²ÎÊı p        £º´æ·Å24Ğ¡Ê±ÎÂ¶ÈµÄÊı×é
//²ÎÊı Month    £ºÔÂ·İ
//²ÎÊı Day      £ºÈÕÆÚ
//²ÎÊı LOCATION £ºµØÇø´úºÅ
//·µ»ØÖµ        £º·µ»ØÊÇ·ñ²éÑ¯µ½
/*  µØÇø´úºÅÈçÏÂ(ÒÑ¾­define¹ı)
	 HAERBIN   1  ¹ş¶û±õ
	 SHENYANG  2  ÉòÑô
	 BEIJING   3  ±±¾©
	 JINAN     4  ¼ÃÄÏ
	 HEFEI     5  ºÏ·Ê
	 CHANGSHA  6  ³¤É³
	 GUANGZHOU 7  ¹ãÖİ
	 HAIKOU    8  º£¿Ú
	 DULAN     9  ¶¼À¼
	 WULUMUQI  10 ÎÚÂ³Ä¾Æë*/
	bool getHistoryTemVec(float p[24], int Month, int Day, int LOCATION);
<<<<<<< HEAD


	/*¡­¡­¡­¡­getEstTemVec »ñÈ¡Ô¤²âÊ±¼äÇúÏßµÄº¯Êı¡­¡­¡­¡­*/
//²ÎÊı TempMax TempMin £ºÊäÈëÒ»ÈÕÎÂ¶È×î´ó×îĞ¡Öµ
//²ÎÊı TimeMax TimeMin £ºÊäÈëÒ»ÈÕÎÂ¶È×î´ó×îĞ¡Öµ³öÏÖµÄÊ±¼ä £¨Ò»°ãTimeMaxÎª15×óÓÒ£¬TimeMinÎª5×÷Òµ£©
//Êä³ö£ºÒ»¸ö³¤¶ÈÎª24µÄÊı×é£¬±íÊ¾ÎÂ¶È´óĞ¡
	void getEstTemVec(float p[24], float TempMax, float TempMin, int TimeMax, int TimeMin);




	std::string m_libPath;  // ´æ´¢ÎÂ¶È¼ÇÂ¼µÄÎÄ¼ş¼ĞÂ·¾¶
=======
>>>>>>> bddcc0a... ä¿®æ”¹ç›¸åº”çš„å½¢å¼



};

/*ÈÕÆÚºÍ»ıÈÕ¶ÔÓ¦Êı×é*/
extern  int Month_day_JD[][3];