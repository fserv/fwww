#ifndef _X_TIME_H_
#define _X_TIME_H_

#include <time.h>
#include <string>

std::string tostr( int n );

typedef struct tm Tm;

class XTime
{
	public: 
		static void NowMonthYear( int &mon, int &year );
		static void MonthDay( time_t sec,  int &mon, int &day );
		static void YearMonthDay( time_t sec,  int &year, int &mon, int &day );
		static void TodayYearMonthDay( int &year, int &mon, int &day );
		static void YesterdayYearMonthDay( int &year, int &mon, int &day );
		static void LocalYearMonthDay( time_t sec,  int &year, int &mon, int &day );
		static void YearMonthDayHourMin( time_t sec,  int &year, int &mon, int &day, int &hour, int &min );
		static std::string MonthStr(int month );
		static std::string GetDate(time_t  sec );
		static std::string GetDateHHMM(time_t  sec );
		static std::string GetDateOnly(time_t  sec );
		static std::string GetShortDate(time_t sec );
		static std::string GetShortDate2(time_t sec );
		static std::string GetServerDateStr(time_t  sec );
		static std::string GetServerDateStr(const std::string &sec );
		//static std::string GetLongSecStr();
		//static time_t GetLongSec();
		static std::string getNowTime();
		static std::string GetYYYYMMDD();
		static std::string GetYYYY_MM_DD();
		static std::string GetYYYY_MM();
		static std::string GetYYYY();
		static std::string GetYYYYDMMDDD(time_t sec );


};

#endif
