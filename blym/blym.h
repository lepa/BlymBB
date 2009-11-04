#include <iostream>
#include <string>


typedef std::string String;

class sput
{
public:
	sput();
	void echo ( String allyouwant ); 
	String get ( String& varname );
	String post ( String& varname );
};


