#include "blym.h"

sput::sput ()
{
	this->echo("Content-type: text/html\n\n");
}

void sput::echo (String allyouwant)
{
	std::cout  << allyouwant;
}



