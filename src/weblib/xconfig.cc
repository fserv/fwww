#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "ssplit.h"
#include "xconfig.h"

// static: get value from environment variable
sstr XConfig::getEnv(const char *name) 
{
	char  buf[256];
	strcpy( buf, "");

	char *p = getenv(name);
	if ( NULL == p ) {
		return "";
	} else {
		strcpy(buf, p );
		return buf;
	}
}

// given progName, open progName.conf for parameters
XConfig::XConfig( const sstr &progName )
{
    // open the file and store it into hash table
    //  suffix     contentType
    // ---------------------------------------
    //  XENV_P1=value1
    //  XENV_P2=value2
    //  XENV_P3=value3


	// sstr configFile = progName + ".conf";
	ssplit arp(progName, '.');

    // if exe is  aaa.exe then conf file is ../conf/aaa.conf
	sstr configFile = "../conf/" + arp[0] + ".conf";
    FILE *fp = fopen(configFile.c_str(), "r");
    char line[1024];
    sstr str;
    sstr name, value;

	if ( NULL == fp ) {
		return;
	}

    while( NULL != (fgets(line, 1024, fp )) )
    {
		if ( '\0' == line[0] ) break;

        str = line;
		str.erase(str.find_last_not_of(" \t\n\r")+1);
        if ( line[0] == '#' )
        {
            continue;
        }

        ssplit ar( str, '=' );
        if ( ar.length() <= 1 ) {
            continue;
        }

        name = ar[0];
        value = ar[1];

        hash_[name] = value;
    }

    fclose(fp );

}

XConfig::~XConfig()
{
}

sstr XConfig::getValue( const sstr &name ) const
{
	auto itr = hash_.find( name );
	if ( itr == hash_.end() )
	{
		return "";
	}

    return itr->second;
}

void XConfig::print()
{
	printf("XConfig::print:\n");
	for ( auto &itr : hash_ )
	{
		printf("key=[%s]  value=[%s]\n", itr.first.c_str(), itr.second.c_str() );
	}
	printf("\n");
}

