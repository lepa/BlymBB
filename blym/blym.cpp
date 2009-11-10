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
String sput::GET ( String& varname )
{
	char* p;
	String query, res="";

// If there is a get request 
	if ((( p = std::getenv( "QUERY_STRING" )) != NULL) )	
	{
		query = p;

		if ( query.find( varname ) != -1 )    //If find varname
			res = query.substr (		   //Create a substring
				query.find ( varname )+1,   //That starts at varname's position +1
				query.find ( "&" )          //And ends when finds an & or at the end of the string
			);
	} 

	return res;
}



//Method to find POST requests
String sput::POST ( String& varname )
{
	String query, res="";
	int length;

	//Gets the content length
	if ( std::sscanf( getenv("CONTENT_LENGTH"), "%d", &length ) == 1 ) 
	{
		std::getline (std::cin, query, '\0' );
	
		if ( query.find( varname ) != -1 ) 
			res = query.substr (
				query.find ( varname )+1,
				query.find ( "&" )
			);
	} 

	return res;
}



//Method to get the web client ip
char* sput::get_client_ip()
{
	return getenv ( "REMOTE_ADDR" );
}



//The name is explicative
String sput::htmlentities ( String to_escape )
{
	int i=0;
	char* entity;

	do {
		if ( (to_escape[i] >= 'A' && to_escape[i] <= 'Z') || 
			(to_escape[i] >= 'a' && to_escape[i] <= 'z') || 
			(to_escape[i] >= '0' && to_escape[i] <= '9') )  
		{
			i++; 
		}
		else 
		{
			std::sprintf ( entity, "&#%2d;", (int) to_escape[i] );
			to_escape.replace ( i, 1, entity );
			i += std::strlen (entity );
		}
	} while ( i < to_escape.length() );

	return to_escape;
}

