#ifndef _xconfig_h_
#define _xconfig_h_
#include <string>
#include <unordered_map>

using sstr = std::string;

class XConfig
{
	public:

		static sstr getEnv( const char *name ) ;

        XConfig( const sstr &confName );
        ~XConfig();

        sstr getValue( const sstr &name ) const ;
        void print();

	private:
		std::unordered_map<sstr, sstr> hash_;
};

#endif
