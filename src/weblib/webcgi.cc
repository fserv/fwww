/*
 *      All right resoved by 5840 company
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "webcgi.h"
#include "ssplit.h"

char XCGI::buf_[]={' '};
char XCGI::buf1_[]={' '};
char XCGI::buf2_[]={' '};

////////////////////////////////////////////////////////////////////////////////
// Function public constructor
// Input: stdin from browser
// Output: none
// Comments: ctor for CGI related
// Side-effects:
// Revised by:         Date:
////////////////////////////////////////////////////////////////////////////////
XCGI::XCGI()
{
	rec_ = NULL;
	length_ = 0;
	isFormData_ = 0;

	inStr_ = "";

	if ( IsPost() ) {
		GetStdinStr( inStr_ );
	} else {
		char *p = getenv("QUERY_STRING");
		if ( p != NULL ) {
			inStr_ = sstr(p);
		}
	}

	// getForm();
	getForm2();
}

XCGI::~XCGI()
{
	if ( NULL != rec_ ) {
		delete [] rec_;
		rec_ = NULL;
	}
}


// public
sstr XCGI::ENV( const char *envName )
{
	sstr val="";

	char *p = getenv( envName );
	if ( p != NULL ) {
		val = p;
	}
	return val;
}


// public
sstr XCGI::GetValue( const sstr &name ) const
{
	sstr value;

	GetValueFromsstr2( inStr_, name, value );
	return value;
}

sstr
XCGI::GetValue( const char *name ) const
{
	sstr value;

	GetValueFromsstr2( inStr_, name, value );
	return value;
}

// public
sstr
XCGI::GetFormValue( const char *name ) const
{
	for ( int i=0; i < length_; i ++) {
		if ( rec_[i].name == name ) {
			return rec_[i].value;
		}
	}
	return "";
}

// public
sstr
XCGI::GetInput() const
{
	return inStr_;
}

void XCGI::SetInput(const sstr &inpstr )
{
	inStr_ = inpstr;
}

// ==========================================================================
// private
void
XCGI::GetValueFromsstr( const char *qstr, const char *name, sstr & value )  const
{
        const char *start = NULL; 
        const char *end = NULL; 
        const char *p;
		value = "";

        static  char buf1[2];

		sstr fname;

        if ( *qstr == '\0' || name[0] == '\0' ) {
            return;
        }

		fname = sstr("&") + name + "=";
        start = strstr(qstr, fname.data() ); 
        if (  NULL == start ) {
			fname = sstr(name) + "=";
			start = strstr(qstr, fname.data() );
			if ( NULL != start && start == qstr  )
			{
			} else {
				return;
			}
        }

        end = strstr(start, "=" );
        if (  NULL == end ) {
                return; 
        }

        start = end + 1;
        for ( p=start; *p != '&' && *p != '\0'; p++ ) {
                if ( *p == '+' ) {
						value += ' ';
                } else if ( *p == '%' ) {
					if ( *(p+1) != '\0' && *(p+2) != '\0' )
					{
                        buf1[0] = *(p+1);
                        buf1[1] = *(p+2);
                        p += 2;

                        value += HexsstrToByte( buf1 );
					} else {
                         value += *p;
					}
                } else {
                         value += *p;
                }
        }

		// value += '\0';
}

// private
void
XCGI::GetValueFromsstr2( const sstr &qstr, const sstr &name, sstr & value )  const
{
        char *start = NULL; 
        char *end = NULL; 
        char *p;
		value = "";

		ssplit ar (qstr, '&');  // a=xxx&c=xxx  or a=xxx
		int len = ar.length();
		if ( len < 1) return;


		int  i=0;
		sstr pair;
		sstr qname, qval;
		int  found=0;

		for  (i=0;i < len ; i++)
		{
			pair = ar[i];
			ssplit ar2(pair, '=');
			qname = ar2[0];
			if ( qname == name )
			{
				if ( ar2.length() == 1 )  // "name" or "name="
				{
					qval = "";
				} else {
					qval = ar2[1];
				}

				found = 1;
				break;
			}

		}

		if ( ! found )  return;
		if ( qval == "" ) return;

		// change qval to url decoded real string binary

        static  char buf1[2];
		sstr nval;

        for ( p= (char*) qval.c_str(); *p != '\0'; p++ )
        {
                if ( *p == '+' )
                {
						nval += ' ';
                } else if ( *p == '%' ) {
					if ( *(p+1) != '\0' && *(p+2) != '\0' )
					{
                        buf1[0] = *(p+1);
                        buf1[1] = *(p+2);
                        p += 2;

                        nval += HexsstrToByte( buf1 );
					} else {
                         nval += *p;
					}
                } else {
                         nval += *p;
                }
        }

		// value += '\0';
		value = nval;
}

// private
int
XCGI::IsPost()
{
        char *contentLength = getenv("CONTENT_LENGTH");

        if ( NULL == contentLength )
        {
                return 0;
        }

        int len = strtol(contentLength, NULL, 10);
        if ( len < 1 ) {
                return 0;
        }

        return 1;
}

// private
void
XCGI::GetStdinStr( sstr &stdinStr )
{
        char *contentLength = getenv("CONTENT_LENGTH");

        if ( NULL == contentLength ) {
            return;
        }

        int len = strtol(contentLength, NULL, 10);
        if ( 0 == len ) {
            return; 
        }

        int ch;
        while ( EOF != (ch=getchar() ) ) {
			// if ( ch != '\r' && ch != '\n' )
			stdinStr += ch;

			/*** Content-Type maynot be there
			if ( strstr(stdinStr.s(), "form-data") && 
				 strstr(stdinStr.s(), "Content-Type") )
				 *****/

			if ( strstr(stdinStr.c_str(), "form-data") ) 

			 {
			 	isFormData_ = 1;
				// break;
				// todo ???? why break here ???
			 }

			 if ( ch == '\n' )
			 {
			 	if ( strstr(stdinStr.c_str(), "filename") )
				{
					break; 
					// afterwards are file contents and separators
					// we specially designed in HTMl page so that all form variables
					// and hidden names are before the uploaded file content
				}
			 }
        }

		if ( isFormData_ )
		{
			// get boundary_
			const char *beg = strstr(stdinStr.c_str(), "----");
			const char *end = strchr(beg, '\n');
			if ( *(end-1) == '\r' ) end--;
			int boundaryLen = end - beg;
			sstr b(beg, boundaryLen );
			boundary_ = b;

			// extract sid, section, cmd, path, filename
			char section[32];
			char sid[64];
			char cmd[64];
			// char domain[64];
			char path[128];
			char filename[128];
			GetFormDataValue( stdinStr.c_str(), "section", section);
			GetFormDataValue( stdinStr.c_str(), "cmd", cmd);
			GetFormDataValue( stdinStr.c_str(), "sid", sid);
			GetFormDataValue( stdinStr.c_str(), "path", path);
			// GetFormDataValue( stdinStr.c_str(), "domain", domain);
			GetUploadFileName( stdinStr.c_str(), filename );

			stdinStr="section="+sstr(section) +
					 "&cmd=" + cmd +
					 "&sid=" + sid +
					 "&path=" + path +
					 // "&domain=" + domain +
					 "&filename=" + filename  +
					 "&boundary=" + boundary_
					 ;
		}

}


// private
int 
XCGI::HexsstrToByte( char *buf ) const
{
    int  d1 = CharToDigi( buf[0] );
    int  d2 = CharToDigi( buf[1] );

    return ( d1 * 16 + d2 );
}

// private
int 
XCGI::CharToDigi( char c ) const
{
    int d;

    if ( '0' == c )
    {
        d = 0;
    }
    else if ( '1' == c )
    {
        d = 1;
    }
    else if ( '2' == c )
    {
        d = 2;
    }
    else if ( '3' == c )
    {
        d = 3;
    }
    else if ( '4' == c )
    {
        d = 4;
    }
    else if ( '5' == c )
    {
        d = 5;
    }
    else if ( '6' == c )
    {
        d = 6;
    }
    else if ( '7' == c )
    {
        d = 7;
    }
    else if ( '8' == c )
    {
        d = 8;
    }
    else if ( '9' == c )
    {
        d = 9;
    }
    else if ( 'A' == c || 'a' == c )
    {
        d = 10;
    }
    else if ( 'B' == c || 'b' == c )
    {
        d = 11;
    }
    else if ( 'C' == c || 'c' == c )
    {
        d = 12;
    }
    else if ( 'D' == c || 'd' == c )
    {
        d = 13;
    }
    else if ( 'E' == c || 'e' == c )
    {
        d = 14;
    }
    else if ( 'F' == c || 'f' == c )
    {
        d = 15;
    }
    else
    {
        d = c;
    }

    return d;
}

// inStr_ is "addrid=1&who=++&abc=jgfgf&bb=%33&name=Jack+Triper"
void
XCGI::getForm()
{
	int num = 1;
	char *p = (char*) inStr_.data();

	// jyue jan2
	if ( *p == '\0' || inStr_.length()<1 )
	{
		length_ = 0;
		return;
	}


	while(  NULL != ( p = strchr(p, '&') )  )
	{
		p++; num ++;
	}

	if ( rec_ != NULL ) { delete [] rec_; }

	length_ = num;
	rec_ = new XFORMREC[length_];

	char *start, *end;
	start = (char*) inStr_.data();
	int recNum = 0;
	int len;
	sstr buf1, buf2;
	while( 1 )
	{
		end = start + 1;
		for ( end = start + 1; *end != '\0'; end ++ )
		{
			if ( *end == '&' )
			{
				break;
			}
		}

		len = end - start;

		strncpy( buf_, start, len );
		buf_[len]='\0';

		GetNameValue( buf_, buf1, buf2 );
		processURLValue( buf1 );
		processURLValue( buf2 );

		rec_[recNum].name=buf1;
		rec_[recNum].value=buf2;
		recNum ++;

		if ( *end == '\0' )
		{
			break;
		}
		else
		{
			start = end + 1;
			if ( *start == '\0' ) break;
		}
	}

}


// inStr_ is "addrid=1&who=++&abc=jgfgf&bb=%33&name=Jack+Triper"
void
XCGI::getForm2()
{
	int num = 1;
	// char *p = (char*) inStr_.data();

	if ( inStr_.length() < 1 )
	{
		length_ = 0;
		return;
	}

	ssplit arr(inStr_, '&' );
	num = arr.length();  // 1: name=xxx  2: name=xxx&bbb=xxx

	if ( rec_ != NULL ) { delete [] rec_; }

	length_ = num;
	rec_ = new XFORMREC[num];

	int i;
	sstr pair, name, value;
	for ( i = 0; i < num; i++)
	{
		pair = arr[i];
		ssplit ar2(pair, '=');
		if ( ar2.length() == 1 )  // 1: nameonly or "name="  2: name=value
		{
			name = ar2[0];
			value = "";
		}
		else
		{
			name = ar2[0];
			value = ar2[1];
		}

		processURLValue( name );
		processURLValue( value );

		rec_[i].name=name;
		rec_[i].value=value;
	}

}


XFORMREC& XCGI::operator[](int i ) const
{
	return rec_[i];
}

int  XCGI::formLength() const
{
	return length_;
}

void
XCGI::delForm()
{
	if ( NULL != rec_ )
	{
		delete [] rec_;
		rec_ = NULL;

		length_ = 0;
	}
}

void XCGI:: processURLValue( sstr &value )
{
	if ( value == "++" ) 
	{
		value ="";
		return ;
	}

	// value="%3Ffiles.txt"
	sstr oldstr; 
	oldstr = value;
	static char buf2[2];
	value="";
	for( char *p=(char*) oldstr.c_str(); *p != '\0'; p++)
	{
		// added later by jyue dec20, 2003
        if ( *p == '+' )
        {
			value += ' ';
        }

		// if ( *p == '%' )
		else if ( *p == '%' )
		{
			if ( *(p+1) != '\0' && *(p+2) != '\0' )
			{
				buf2[0] = *(p+1);
				buf2[1] = *(p+2);
				value += HexsstrToByte(buf2);
				p += 2;
			}
			else
			{
				value += *p;
			}
		}
		else
		{
			value += *p;
		}
	}

}

void XCGI::GetFormDataValue( const char *str, const char *name, char *value )
{
    strcpy(value, "");

    const char *p = NULL;
    p = strstr(str, name );
    if ( NULL == p ) return;

    const char *pn1 = strchr( p, '\n' );
    const char *pn2 = strchr( pn1+1, '\n' );
    const char *beg = pn2+1;
    const char *end = strchr(beg, '\n');

    int len = end - beg;
    strncpy( value, beg, len );
    value[len]='\0';

    if ( value[len-1] == '\r' )
    {
         value[len-1] = '\0';
    }
}


// send what ever to DS, so multiple fils can be uploaded
void XCGI::ReadAndUpload( int sockfd ) const
{
	int len1=0;
	char buf1[16384];

	int num=0;
	while (1)
	{
	    len1=fread( buf1, 1, 16384,  stdin ); 
		if ( len1 <= 0 ) 
			break;
		else
			::write( sockfd, buf1, len1);
	}
}

void XCGI::GetUploadFileName(const char *str, char *fileName)
{
    strcpy( fileName, "" );

    const char *p = strstr(str, "filename=");
    if ( NULL == p ) return;

    const char *begq = NULL;
    begq = strchr(p, '\"');
    const char *endq = NULL;
    endq = strchr( begq+1, '\"');
    int len = endq - begq-1;

    if ( len < 1 ) return;

    char fullpath[512];

    strncpy( fullpath, begq+1, len);
    fullpath[len] = '\0';

    const char *slash = NULL;
    slash = strrchr(fullpath, '\\');
    if ( NULL == slash  )
    {
        slash = strrchr(fullpath, '/');
    }

    if ( NULL == slash )
    {
        strcpy( fileName, fullpath );
    }
    else
    {
        strcpy( fileName, slash+1);
    }
}

void XCGI::GetNameValue( const sstr &pair, sstr &name, sstr &value )
{
    if ( NULL == (strchr(pair.c_str(), '=') ) )
    {
        name=pair;
        value="";
        return;
    }

    int n;
    char *p;
    char pn[32];
    char pv[256];

    n=0;
    for( p=(char*)pair.c_str(); *p != '='; p++)
    {
        pn[n++] = *p;
    }
    pn[n] = '\0';
    name = pn;

    n=0;
    for( p=p+1; *p != '\0'; p++)
    {
        pv[n++] = *p;
    }
    pv[n] = '\0';
    value = pv;
}

