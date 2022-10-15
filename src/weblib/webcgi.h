/*
 *   All right resirved by datajaguar company
 */
#ifndef _XCGI_H_
#define _XCGI_H_
#include <string>

using sstr = std::string;

struct XFORMREC { sstr name; sstr value; };

class XCGI
{   
    public:
		XCGI();
		~XCGI();

        static sstr ENV( const char *envName );
		sstr GetValue(const char *name) const ;
		sstr GetValue(const sstr &name) const ;
		void GetValueFromsstr(const char *qstr, const char *name, sstr &value) const;
		void GetValueFromsstr2(const sstr& qstr, const sstr & name, sstr &value) const;
		sstr GetFormValue( const char *name ) const;
		sstr GetInput() const; 
		void SetInput(const sstr &inpstr); // test purpose only 
		void getForm() ;
		void getForm2() ;
		void delForm();
		XFORMREC& operator[](int i ) const;
		int  formLength() const;
		int  isFormData() const { return isFormData_; }
		void ReadAndUpload( int sockfd ) const;
		sstr boundary_;

    private:
		sstr inStr_;
		XFORMREC *rec_;
		int		length_;
		static  char buf_[256];
		static  char buf1_[256];
		static  char buf2_[256];
		int IsPost();
		int isFormData_;
		void GetStdinStr( sstr &stdinStr );
		int HexsstrToByte( char *buf ) const ;
		int CharToDigi( char c ) const ;
		void processURLValue( sstr &value );
		void GetFormDataValue( const char *str, const char *name, char *value );
		void GetUploadFileName( const char *str, char *fileName);
		void GetNameValue( const sstr &pair, sstr &name, sstr &value);
};


#endif
