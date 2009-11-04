#include "blym.h"

// Constructor
sput::sput ()
{
	//Says that the content is simple html 
	this->echo("Content-type: text/html\n\n");
}

//Method to send queries in output
void sput::echo (String allyouwant)
{
	std::cout  << allyouwant;
}

//Method to find GET requests
String GET ( String& varname )
{
	char* p;
	String query, res="";

	if ((( p = std::getenv( "QUERY_STRING" )) != NULL) )	
	{
		query = p;

		if ( query.find( varname ) != -1 )
			res = query.substr (
				query.find ( varname ),
				query.find ( "&" )
			);
	} 

	return res;
}

//Method to find POST requests
String POST ( String& varname )
{
	String query, res="";
	int length;

	if ( std::sscanf( getenv("CONTENT_LENGTH"), "%d", &length ) == 1 ) 
	{
		std::getline (std::cin, query, '\0' );
	
		if ( query.find( varname ) != -1 )
			res = query.substr (
				query.find ( varname ),
				query.find ( "&" )
			);
	} 

	return res;
}




