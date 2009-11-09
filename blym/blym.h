#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>

typedef std::string String;

class sput
{
public:
	sput();
	void echo ( String ); 
	String GET ( String& );
	String POST ( String& );
	char* get_client_ip();
	String htmlentities ( String );
};


