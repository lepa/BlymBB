#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

typedef std::string String;

class sput
{
public:
	sput();
	void echo ( String allyouwant ); 
	String GET ( String& varname );
	String POST ( String& varname );
	char* get_client_ip();
};


