/*
 *	Fastserv.exe main function here
 *	All right resoved by 5840 company
 */

#include <fcgi_stdio.h>
#include <sys/stat.h>
#include <string.h>

#include "xconfig.h"
#include "webcgi.h"
#include "xparam.h"
#include "ssplit.h"
#include "xtime.h"

void processCmd (const XCGI &cgi, XParam &param);

void printMsg(const char *msg)
{
    FCGI_fprintf(FCGI_stdout, "Content-Type: text/html\r\n");
    FCGI_fprintf(FCGI_stdout, "Content-Length: %d\r\n\r\n", strlen(msg) );
    FCGI_fprintf(FCGI_stdout, "%s", msg );
    FCGI_fflush(FCGI_stdout);
}


FCGI_FILE *g_log;
XConfig *g_xconfig;
int   g_debug;
sstr g_accessip;
sstr g_accessip_control;
sstr  g_sessdb;
unsigned long g_num=0;

static int ipInList(const sstr &ip );

int main(int argc, char *argv[])
{
	XParam param;
	sstr sid, browserip, srv;

    time_t nowt = time(NULL);
    int toYear, toMonth, toDay;
    XTime::LocalYearMonthDay( nowt, toYear, toMonth, toDay );
	sstr logfpath; 
	logfpath += "/tmp/fwww"; 
	logfpath += tostr(toYear) + "-" + tostr(toMonth) + "-" + tostr(toDay ) + ".log";

	umask(0);
	g_xconfig = new XConfig(argv[0]);

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

	while(FCGI_Accept() >= 0)
	{
		XCGI  cgi;
		sid = cgi.GetValue("sid");
		browserip = cgi.ENV("REMOTE_ADDR");
		param.sid = sid;
		param.browserip = browserip;

		processCmd(cgi, param);
	}

	FCGI_Finish();
	FCGI_fclose(g_log);

	delete g_xconfig;
	return 100;
}

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

// Process commands for each request
// Input: cgi and param
void processCmd (const XCGI &cgi, XParam &param)
{
	sstr section=cgi.GetValue("section");
	sstr cmd=cgi.GetValue("cmd");
	sstr lang=cgi.GetValue("lang");
	sstr browserip = param.browserip;

	if ( g_debug ) {
		FCGI_fprintf(g_log, "fwww received [%s]\n", cmd.c_str() );
		FCGI_fflush(g_log);
	}

	// auth IP

	// Greetings
	sstr msg;
	msg += sstr("<br><br>");
	msg += sstr("<center>");
	msg += sstr("<h1>Hello World!</h1>");
	msg += sstr("<h3>Powered by fwww (github.com/fserv/fwww)</h3>");
	msg += sstr("<h4>Your IP address is: ") + browserip + "</h4>";
	msg += sstr("</center>");
	printMsg( msg.c_str() );

	/***
	if (section == "addr")
	{
		Addr(cgi, param);
	}
	else if (section == "login")
	{
		Login(cgi, param);
	}
	else
	{
		printMsg(IDS_ERROR + " unknown section" );
		Svc(cgi, param);
	}
	***/
}

