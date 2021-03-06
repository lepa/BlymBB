#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <exception>
#include <curl/curl.h>
#include <map>

typedef std::string String;
typedef std::map<String,String> StringMap;

class blym
{
public:
	blym ();
	explicit blym (StringMap&); 

	String file_get_contents (String);
	String sql_escape (String);

	String& htmlentities (String&);
	String& nl2br (String&);

	StringMap GET;
	StringMap POST;
	StringMap COOKIE;
	
	bool is_set (String);

	template <class T>
	blym& operator<< (T);

protected :
	static int save_data(char*, size_t, size_t, String*);

	void get_GET ();
	void get_POST ();
	void get_COOKIE  ();
};

//The exceptions
class fileExists : public std::exception
{
	const char* what () const throw()
	{
		return "This file exists";
 	}
};

class fOpenError : public std::exception
{
	const char* what () const throw()
	{
		return "Error while opening a file";
	}
};

class connError : public std::exception
{
	const char* what () const throw()
	{
		return "Error while connecting to the internet";
	}
};
