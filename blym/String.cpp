#include "blym.h"

String::String ( int value )
{
	char* str;
	int len = 1, tmp = value;

	while ( tmp ) 
	{
		tmp/=10;
		len++;
	}

	std::malloc (len * sizeof(char));

	std::sprintf (str, "%d", value );

	this = new String (str);
}



