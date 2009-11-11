#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <exception>
#include <sys/socket.h>
#include <netdb.h>

typedef std::string String;

class blym
{
public:
	blym();

	void echo ( String ); 
	blym& operator<<( String& );
	
	String GET ( String );
	String POST ( String );
	String COOKIE ( String );
	
	char* get_client_ip();
	
	String& htmlentities ( String& );
	String& nl2br ( String& );
	String file_get_contents (String& );
};


//The exceptions
class fileExists : public std::exception
{
	const char* what() const throw()
	{
		return "This file exists";
	}
};

class fOpenError : public std::exception
{
	const char* what() const throw()
	{
		return "Error while opening a file";
	}
};

class connError : public std::exception
{
	const char* what() const throw()
	{
		return "Error while connecting to the internet";
	}
};
