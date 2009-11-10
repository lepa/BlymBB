#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <exception>
#include <sys/socket.h>
#include <netdb.h>

#define SAFE 1;
#define UNSAFE 0;

typedef std::string String;


class blym
{
public:
	blym();
	void echo ( String ); 
	blym& operator<<( String& );
	String GET ( String& );
	String POST ( String& );
	char* get_client_ip();
	String htmlentities ( String& );
	String nl2br ( String& );
	String file_get_contents (String& name );
};


//The exceptions
class fileExists : public std::exception
{
	const char* what() const throw()
	{
		return "Already a file with the same name of the one you tryed to save";
	}
} FileExists;

class fOpenError : public std::exception
{
	const char* what() const throw()
	{
		return "Error while opening a file";
	}
} FOpenError;

class connError : public std::exception
{
	const char* what() const throw()
	{
		return "Error while connecting to the internet";
	}
} ConnError;
