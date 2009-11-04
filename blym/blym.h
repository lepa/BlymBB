#include <iostream>
#include <string>


class String : public std::string;


class sput
{
public:
	sput();
	void echo ( String& allyouwant ); 
	String get ( String& varname );
	String post ( String& varname );
};


