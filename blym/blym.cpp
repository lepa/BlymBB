#include "blym.h"
//Exception objects
fileExists FileExists;
connError ConnError;
fOpenError FOpenError;


// Constructor
blym::blym ()
{
	//Says that the content is simple html 
	this->echo ("Content-type: text/html\n\n");
}



//Method to send queries in output
void blym::echo (String allyouwant)
{
	std::cout << allyouwant;
}



//Method to find GET requests
String blym::GET (String varname)
{
	char* p;
	String quer y, res="";

// If there is a get request 
	if ((( p = std::getenv ( "QUERY_STRING" )) != NULL) )	
	{
		query = p;

		if (query.find (varname) != -1)    //If find varname
			res = query.substr (		   //Create a substring
				query.find (varname) +
				varname.length () + 1,   //That starts at varname's position +1
				query.find ("&")          //And ends when finds an & or at the end of the string
			); 
	} 

	return res; 
}



//Method to find POST requests
String blym::POST (String varname)
{
	String query,  res = "";
	int length;
	std::stringbuf buffer;

	//Gets the content length
	if (std::sscanf (getenv ("CONTENT_LENGTH"), "%d", &length) == 1) 
	{
		std::cin.get (buffer); 
		query = buffer.str ();
			
		if (query.find (varname) != -1) 
			res = query.substr (
				query.find (varname) +
				varname.length () + 1,
				query.find ("&")
			);
	} 

	return res;
}



//Method to get the web client ip
char* blym::get_client_ip()
{
	return getenv ("REMOTE_ADDR");
}



//The name is explicative
String& blym::htmlentities (String& to_escape)
{
	int i = 0; 
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
			std::sprintf (entity, "&#%2d;", (int) to_escape[i]);
			to_escape.replace (i, 1, entity);
			i += std::strlen (entity ); 
		} 
	} while (i < to_escape.length ());

	return to_escape;
}



//Method to change new lines with <br />
String& blym::nl2br ( String& to_escape )
{
	int i = 0;

	while ( (i = to_escape.find ('\n', i)) != -1)
	{
		to_escape.replace (i, 1, "<br />"); 
		i++;
	}

	return to_escape; 
}
// Needed for cURL 
int blym::save_data (char *data, size_t size, size_t nsize, String *buffer)
{
  	int result = 0;
	if (buffer != NULL)
	{
 		buffer->append (data, size * nsize);
 		result  = size * nsize;
	}
	return result;
}

String content; 

//Method used to get the content of files or web pages
String blym::file_get_contents (String name)
{
	int i = 0;
	if (name.compare (0,7, "http://") == 0)
	{
		CURL* ch = curl_easy_init ();
		curl_easy_setopt (ch, CURLOPT_URL, (name.substr (7,name.find ('/',8))).c_str ());
		curl_easy_setopt (ch, CURLOPT_HEADER, 0);
		curl_easy_setopt (ch, CURLOPT_WRITEFUNCTION, blym::save_data); 
		curl_easy_setopt (ch, CURLOPT_WRITEDATA,&content);
		curl_easy_perform (ch);
		curl_easy_c leanup (ch);
	} 
	else 
	{
 		std::stringbuf buffer;
		std::ifstream file (name.c_str ());
		
		if (file.fail ())
			throw ConnError;
		String sent;
		while (getline (file, sent))
		{
			content.append (sent.append ("\n"));
		} 
	file.close ();
	}

 	return content; 
}



//Method for cookies
String blym::COOKIE (String name)
{
	String cookies = std::getenv ("HTTP_COOKIE");

	return cookies.substr ( 
			cookies.find  (name)
			+ name.length () + 1,
			cookies.find ("; ")
			);
}

String blym::sql_escape (String query)
{
	String keys[] = {"INSERT","AND","UNION","SELECT","CONCAT","/","+"," "};
	for (int i=0; i<= (sizeof (keys) / sizeof (String)); i++)  {
		if (query .find (keys[i]) != String::npos)
			return query.erase (query.find (keys[i]));
		else
			continue; 
	}
	return query; 
}
