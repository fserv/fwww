#ifndef _com_strsplit_h_
#define _com_strsplit_h_
//#include "omicrodef.h"

using sstr = std::string;

class ssplit
{
	public:   
		ssplit();
		ssplit(const sstr& str, char sep = ' ', bool ignoreregion=false );
		ssplit(const char *str, char sep = ' ', bool ignoreregion=false );
		
		void init(const char *str, char sep=' ', bool ignoreregion=false );

		void destroy();
		~ssplit();

	    const sstr& operator[](int i ) const;
	    sstr& operator[](int i );
		sstr& last() const;
		long  length() const;
		long  size() const;
		long  slength() const;
		bool  exists(const sstr &token) const;
		bool  contains(const sstr &token, sstr &rec ) const;
		void  print() const;
		void  printStr() const;
		void  shift();
		void  back();
		const char *c_str() const;
		void  pointTo( const char* str );

	private:
		sstr *list_;
		long length_;
		char sep_;
		int  start_;
		sstr _NULL;
		const char* pdata_;
};

#endif

