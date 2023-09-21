/*
 *	Fastserv.exe main function here
 *	All right reserved by JaguarDB team
 */

#include <fcgi_stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <string>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>

#include <JaguarAPI.h>
#include <xconfig.h>
#include <webcgi.h>
#include <xparam.h>
#include <ssplit.h>
#include <xtime.h>

void processCmd (JaguarAPI &jag, const XCGI &cgi, XParam &param);

std::string intToStr(int i)
{
    char buf[32];
    sprintf(buf, "%d", i);
    return buf;
}

void printMsg(const char *msg)
{
    FCGI_fprintf(FCGI_stdout, "Content-Type: text/html\r\n");
    FCGI_fprintf(FCGI_stdout, "Content-Length: %d\r\n\r\n", strlen(msg) );
    FCGI_fprintf(FCGI_stdout, "%s", msg );
    FCGI_fflush(FCGI_stdout);
}

void printJson(const char *msg)
{
    FCGI_fprintf(FCGI_stdout, "Content-Type: application/json\r\n");
    FCGI_fprintf(FCGI_stdout, "Content-Length: %d\r\n\r\n", strlen(msg) );
    FCGI_fprintf(FCGI_stdout, "%s", msg );
    FCGI_fflush(FCGI_stdout);
}


FCGI_FILE   *g_log;
XConfig     *g_xconfig;
int         g_debug;
sstr        g_accessip;

int ipInList(const sstr &ip )
{
	ssplit ar(g_accessip, '\n');
	int len = ar.length();
	sstr tok;
	for (int i=0; i<len; i++)
	{
		tok = ar[i];
		if ( strstr(ip.c_str(), tok.c_str() ) )  
		{
			return 1;
		}
	}

	return 0;
}


int main(int argc, char *argv[])
{
	XParam param;
	sstr sid, browserip, srv;

    time_t   nowt = time(NULL);
    int      toYear, toMonth, toDay;
    XTime::LocalYearMonthDay( nowt, toYear, toMonth, toDay );
	sstr     logfpath; 

	logfpath += "../log_root/fwww"; 
	logfpath += tostr(toYear) + "-" + tostr(toMonth) + "-" + tostr(toDay ) + ".log";

	umask(0);
	g_xconfig = new XConfig("fwww.conf");

	g_log = FCGI_fopen(logfpath.c_str(), "a");
	if (NULL == g_log) {
		return 10;
	}

	FCGI_fprintf(g_log, "\nfwww starts %s\n", ctime(&nowt));
	FCGI_fflush(g_log);

    g_debug=0;
    sstr debugs;
    debugs = g_xconfig->getValue("XENV_DEBUG");
    if ( debugs == "TRUE" || debugs == "YES" || debugs == "Y" ) {
        g_debug=1;
    }

    JaguarAPI jag;
    int crc = jag.connect( "127.0.0.1", 8888, "admin", "jaguarjaguarjaguar", "vectordb" );
	if ( g_debug ) {
		FCGI_fprintf(g_log, "connecting to 127.0.0.1:8888 rc=%d\n", crc );
		FCGI_fflush(g_log);
	}

	while(FCGI_Accept() >= 0)
	{
		XCGI  cgi;
		sid = cgi.GetValue("sid");
		browserip = cgi.ENV("REMOTE_ADDR");
		param.sid = sid;
		param.browserip = browserip;

		processCmd(jag, cgi, param);
	}

	FCGI_Finish();
	FCGI_fclose(g_log);

	delete g_xconfig;
	return 100;
}


// Process commands for each request
// Input: cgi and param
void processCmd ( JaguarAPI &jag, const XCGI &cgi, XParam &param)
{
	sstr sql;
	sstr reply;

    sql=cgi.GetValue("req");
    if ( sql.size() < 1 ) {
        sql=cgi.GetValue("request");
    }

    if ( 0 == strncasecmp( sql.c_str(), "select", 6) ) {
        reply = "T";
    } else if ( 0 == strncasecmp( sql.c_str(), "describe", 8) ) {
        reply = "T";
    } else if ( 0 == strncasecmp( sql.c_str(), "show", 4) ) {
        reply = "T";
    } else if ( 0 == strncasecmp( sql.c_str(), "list", 4) ) {
        reply = "T";
    } else {
        reply = "F";
    }

	if ( g_debug ) {
		FCGI_fprintf(g_log, "fwww received from client sql=[%s] reply=[%s]\n", sql.c_str(), reply.c_str() );
		FCGI_fflush(g_log);
	}
    
    rapidjson::StringBuffer sbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(sbuf);

    if ( sql.size() < 1 ) {
        jag.execute( sql.c_str() );
        writer.StartArray();
        writer.EndArray();
	    printJson( sbuf.GetString() );
        return;
    }


    if ( reply[0] == 'Y' || reply[0] == 'y' || reply[0] == '1' || reply[0] == 'T' || reply[0] == 't' ) {

        jag.query( sql.c_str() );

        writer.StartArray();
        int  cnt = 0;

	    if ( g_debug ) {
		    FCGI_fprintf(g_log, "fwww sent query sql=[%s] to jaguar\n", sql.c_str() );
		    FCGI_fflush(g_log);
	    }

        while ( jag.fetch() ) {
	        if ( g_debug ) {
		        FCGI_fprintf(g_log, "fwww got one row json=[%s] from jaguar\n", jag.jsonString() );
		        FCGI_fflush(g_log);
	        }

            writer.StartObject();
            writer.Key(intToStr(cnt).c_str());
            writer.String( jag.jsonString() );
            writer.EndObject();
            ++cnt;
        }

        writer.EndArray();
    } else {

        jag.execute( sql.c_str() );

        writer.StartObject();
        writer.Key("Result");
        writer.String("OK");
        writer.EndObject();
    }

	printJson( sbuf.GetString() );
}

