#include <stdio.h>
#include "xtime.h"

std::string tostr( int n )
{
	char buf[32];
	sprintf(buf, "%d", n);
	return buf;
}

void XTime::NowMonthYear( int &mon, int &year )
{
	time_t now = time( NULL );
	Tm *ptm = localtime( &now );
	mon = 1 + ptm->tm_mon;
	year = 1900 + ptm->tm_year;
}

void XTime::MonthDay( time_t sec,  int &mon, int &day )
{
	Tm *ptm = localtime( (time_t*) &sec );
	mon = 1 + ptm->tm_mon;
	day = ptm->tm_mday;
}

void XTime:: TodayYearMonthDay( int &year, int &mon, int &day )
{
	time_t  nowt = time(NULL);
	YearMonthDay( nowt,  year, mon, day );
}

void XTime:: YesterdayYearMonthDay( int &year, int &mon, int &day )
{
	time_t  nowt = time(NULL);
	nowt -= 86400;

	YearMonthDay( nowt,  year, mon, day );
}

void XTime:: YearMonthDay( time_t sec,  int &year, int &mon, int &day )
{
	Tm *ptm = localtime( (time_t*) &sec );
	year = 1900 + ptm->tm_year;
	mon = 1 + ptm->tm_mon;
	day = ptm->tm_mday;
}

void XTime:: LocalYearMonthDay( time_t sec,  int &year, int &mon, int &day )
{
	Tm *ptm = localtime( (time_t*) &sec );
	year = 1900 + ptm->tm_year;
	mon = 1 + ptm->tm_mon;
	day = ptm->tm_mday;
}

// returns 02/13/01
std::string XTime::GetServerDateStr(time_t sec )
{
	Tm *ptm = localtime( (time_t*) &sec );
	int year, mon, day;
	year = 1900 + ptm->tm_year;
	year -= 2000;
	mon = 1 + ptm->tm_mon;
	day = ptm->tm_mday;

	char buf[9];
	sprintf(buf, "%02d/%02d/%02d", mon, day, year );

	return buf;
}


// returns yyyy-mm-dd
std::string XTime::GetYYYYDMMDDD(time_t sec )
{
	Tm *ptm = localtime( (time_t*) &sec );
	int year, mon, day;
	year = 1900 + ptm->tm_year;
	mon = 1 + ptm->tm_mon;
	day = ptm->tm_mday;

	char buf[9];
	sprintf(buf, "%04d-%02d-%02d", year, mon, day );

	return buf;
}

std::string XTime::GetYYYYMMDD()
{
	time_t sec = time(NULL);

	Tm *ptm = localtime( (time_t*) &sec );
	int year, mon, day;
	year = 1900 + ptm->tm_year;
	// year -= 2000;
	mon = 1 + ptm->tm_mon;
	day = ptm->tm_mday;

	char buf[9];
	// sprintf(buf, "%02d/%02d/%02d", mon, day, year );
	sprintf(buf, "%04d%02d%02d", year, mon, day );

	return buf;
}

std::string XTime::GetYYYY_MM_DD()
{
	time_t sec = time(NULL);

	Tm *ptm = localtime( (time_t*) &sec );
	int year, mon, day;
	year = 1900 + ptm->tm_year;
	// year -= 2000;
	mon = 1 + ptm->tm_mon;
	day = ptm->tm_mday;

	char buf[9];
	sprintf(buf, "%04d-%02d-%02d", year, mon, day );

	return buf;
}

std::string XTime::GetYYYY_MM()
{
	time_t sec = time(NULL);

	Tm *ptm = localtime( (time_t*) &sec );
	int year, mon, day;
	year = 1900 + ptm->tm_year;
	mon = 1 + ptm->tm_mon;

	char buf[9];
	sprintf(buf, "%04d-%02d", year, mon );

	return buf;
}

std::string XTime::GetYYYY()
{
	time_t sec = time(NULL);

	Tm *ptm = localtime( (time_t*) &sec );
	int year, mon, day;
	year = 1900 + ptm->tm_year;

	char buf[9];
	sprintf(buf, "%04d", year );

	return buf;
}

std::string XTime::GetServerDateStr(const std::string &secstr )
{
	return GetServerDateStr( atoll(secstr.c_str()) );
}


void XTime::YearMonthDayHourMin( time_t sec,  int &year, int &mon, int &day, int &hour, int &min )
{
	Tm *ptm = localtime( (time_t*) &sec );
	year = 1900 + ptm->tm_year;
	mon = 1 + ptm->tm_mon;
	day = ptm->tm_mday;
	hour = ptm->tm_hour;
	min = ptm->tm_min;
}

#ifdef XCHINESE
std::string XTime::MonthStr(int month )
{
	std::string mstr;

    if ( month == 1 )
    {
        mstr = "1月";
    }
    else if ( month ==2 )
    {
        mstr = "2月";
    }
    else if ( month == 3 )
    {
        mstr = "3月";
    }
    else if ( month == 4 )
    {
        mstr = "4月";
    }
    else if ( month == 5)
    {
        mstr = "5月";
    }
   else if ( month == 6)
    {
        mstr = "6月";
    }
    else if ( month ==7  )
    {
        mstr = "7月";
    }
    else if ( month ==8  )
    {
        mstr = "8月";
    }
    else if ( month == 9  )
    {
        mstr = "9月";
    }
    else if ( month == 10 )
    {
        mstr = "10月";
    }
    else if ( month == 11 )
    {
        mstr = "11月";
    }
    else if ( month == 12  )
    {
        mstr = "12月";
    }

    return mstr;
}

#else
std::string XTime::MonthStr(int month )
{
	std::string mstr;

    if ( month == 1 )
    {
        mstr = "Jan";
    }
    else if ( month ==2 )
    {
        mstr = "Feb";
    }
    else if ( month == 3 )
    {
        mstr = "Mar";
    }
    else if ( month == 4 )
    {
        mstr = "Apr";
    }
    else if ( month == 5)
    {
        mstr = "May";
    }
   else if ( month == 6)
    {
        mstr = "Jun";
    }
    else if ( month ==7  )
    {
        mstr = "Jul";
    }
    else if ( month ==8  )
    {
        mstr = "Aug";
    }
    else if ( month == 9  )
    {
        mstr = "Sep";
    }
    else if ( month == 10 )
    {
        mstr = "Oct";
    }
    else if ( month == 11 )
    {
        mstr = "Nov";
    }
    else if ( month == 12  )
    {
        mstr = "Dec";
    }

    return mstr;
}

#endif


// ctime returns: "Sat Jan 13 15:37:15 2001"
// returns Sat Jan 13 13:10
std::string XTime::GetDate(time_t sec)
{
	/***
	std::string s = ctime(&sec);
	Arr ar(s);
	std::string tmstr=ar[3];
	Arr ar2(tmstr, ':');
	return ar[0] + " " + ar[1] + " " + ar[2] + " " + ar2[0] + ":" + ar2[1];
	***/

	const char *fmt= "%A %F %H:%M"; // "Fri 2004-11-20 09:24"  or Chinese

	char buf[256];
	int  len=256;
	struct tm *ptm;
	ptm = localtime( & sec );
	strftime( buf, len, fmt, ptm );
	return buf;
}

std::string XTime::GetDateHHMM(time_t sec)
{
	const char *fmt= "%F %H:%M"; // "Fri 2004-11-20 09:24"  or Chinese

	char buf[256];
	int  len=256;
	struct tm *ptm;
	ptm = localtime( & sec );
	strftime( buf, len, fmt, ptm );
	return buf;
}

// ctime returns: "Sat Jan 13 15:37:15 2001"
// returns Jan 13, 2001
std::string XTime::GetShortDate(time_t sec)
{
	const char *fmt= "%F %H:%M"; // "Fri 2004-11-20 09:24"  or Chinese

	char buf[256];
	int  len=256;
	struct tm *ptm;
	ptm = localtime( & sec );
	strftime( buf, len, fmt, ptm );
	return buf;

}

// ctime returns: "Sat Jan 13 15:37:15 2001"
// returns Jan 13 15:37 2001
std::string XTime::GetShortDate2(time_t sec)
{
	const char *fmt= "%F %H:%M"; // "2004-11-20 09:24"  or Chinese

	char buf[256];
	int  len=256;
	struct tm *ptm;
	ptm = localtime( & sec );
	strftime( buf, len, fmt, ptm );
	return buf;

}

// returns Jan 13 15:37 2001
std::string XTime::GetDateOnly(time_t sec)
{
	const char *fmt= "%F"; // "2004-11-20"  or Chinese

	char buf[256];
	int  len=256;
	struct tm *ptm;
	ptm = localtime( & sec );
	strftime( buf, len, fmt, ptm );
	return buf;

}

std::string XTime::getNowTime()
{
    char timestamp[256];
    struct tm *tm_now;
    time_t  ns=time(NULL);
    tm_now = localtime( &ns );
    strftime( timestamp, sizeof( timestamp), "%Y%m%d-%H%M%S-", tm_now);

	return timestamp;
}
