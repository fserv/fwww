/*
 * Copyright (C) Colmar Authors
 *
 * Colmar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Colmar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the LICENSE file. If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <string.h>
#include <string>
#include "ssplit.h"

ssplit::ssplit()
{
	list_ = NULL;
	length_ = 0;
	start_ = 0;
	_NULL = "";
	pdata_ = NULL;
}

ssplit::ssplit(const sstr& str, char sep, bool ignoreregion )
{
	list_ = NULL;
	length_ = 0;
	start_ = 0;
	_NULL = "";
	init( str.c_str(), sep, ignoreregion );
}

ssplit::ssplit(const char *str, char sep, bool ignoreregion )
{
	list_ = NULL;
	length_ = 0;
	start_ = 0;
	_NULL = "";
	init( str, sep, ignoreregion );
}

void ssplit::init(const char *str, char sep, bool ignoreregion )
{
	destroy();
	char *p;

	pdata_ = str;

	list_ = NULL;
	length_ = 0;

	sep_ = sep;
	if ( str == NULL  || *str == '\0' ) return;

	char *start, *end, *ps;
	int len;
	int tokens=1;

	p = (char*) str;
	if ( ignoreregion ) { while ( *p == sep_ ) { ++p; } }

	while ( *p != '\0' ) {
		if ( *p == sep_ ) {
			if ( ignoreregion ) {
				while( *p == sep_ ) ++p;
				if ( *p == '\0' ) break;
			} 
			tokens ++;
		}
		++p;
	}

	list_ = new sstr[tokens];
	length_ = tokens;

	start = ps = (char*) str;
	if ( ignoreregion ) {
		while ( *ps == sep_ ) { ++start; ++ps; }
	}

	end = start;
	int i = 0;
	while(  i <= tokens -1 )
	{
		for( end=start; *end != sep_ && *end != '\0'; end++ ) { ; }
		
		len= end-start;
		if ( len == 0 ) {
			list_[i] = "";
		} else {
			list_[i] = sstr(start, len);
		}

		i++;
		if ( *end == '\0' ) {
			break;
		}

		end++;
		if ( ignoreregion ) {
			while ( *end != '\0' && *end == sep_ ) ++end;
		}
		start = end;
	}

}

ssplit::~ssplit()
{
	destroy();
}

void ssplit::destroy()
{
	if ( list_ ) {
		delete [] list_;
	}
	list_ = NULL;
	length_=0;
}

const sstr& ssplit::operator[](int i ) const
{
	if ( i+start_ < 0 ) return _NULL;

	if ( i < length_ - start_ )
	{
		return list_[start_+i];
	}
	else
	{
		return _NULL; 
	}
}

sstr& ssplit::operator[](int i ) 
{
	if ( i+start_ < 0 ) return _NULL;

	if ( i < length_ - start_ )
	{
		return list_[start_+i];
	}
	else
	{
		return _NULL; 
	}
}

long ssplit::length() const
{
	return length_ - start_;
}
long ssplit::size() const
{
	return length_ - start_;
}

long ssplit::slength() const
{
	return length_ - start_;
}

bool ssplit::exists(const sstr &token) const
{
	for (int i=0; i < length_; i++) {
		if ( 0==strcmp( token.c_str(), list_[i].c_str() ) ) {
		    return true;
		}
	}

	return false;
}

bool ssplit::contains(const sstr &token, sstr &rec) const
{
	const char *tok;
	for (int i=0; i < length_; i++) {
		tok = list_[i].c_str(); 
		if ( strstr( tok, token.c_str() ) ) {
		  	rec = tok;
		  	return 1;
		 }
	}

	rec = "";
	return 0;
}

void ssplit::print() const
{
	printf("s3008 ssplit::print():\n" );
	for (int i=0; i < length_; i++)
	{
		printf("i=%d [%s]\n", i, list_[i].c_str() );
	}
	printf("\n"); 
	fflush(stdout);
}

void ssplit::printStr() const
{
	printf("s3008 ssplit::printStr(): [%s]\n", pdata_ );
}

sstr& ssplit::last() const
{
	return list_[ length_ -1];
}

void ssplit::shift()
{
	if ( start_ <= length_-2 ) {
		++ start_;
	}
}

void ssplit::back()
{
	if ( start_ <= 1 ) {
		-- start_;
	}
}

const char* ssplit::c_str() const
{
	return pdata_;
}

void ssplit::pointTo( const char *str )
{
	pdata_ = str;
}

