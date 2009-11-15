#include "blym.hpp"
//Exception objects
fileExists FileExists;
connError ConnError;
fOpenError FOpenError;


// Constructor
blym::blym ()
{
 	//Tells that the content is simple html 
	*this << "Content-type: text/html\n\n";
	this->get_GET ();
	this->get_POST ();
}


blym& blym::operator<< (String str)
{
	std::cout << str;
}

blym& blym::operator<< (int i)
{
	std::cout << i;
}

blym& blym::operator<< (double i)
{
	std::cout << i;
}

blym& blym::operator<< (float i)
{
	std::cout << i;
}

blym& blym::operator<< (long i)
{
	std::cout << i;
}

blym& blym::operator<< (char c)
{
	std::cout << c;
}


//Method to save GET requests
void blym::get_GET ()
{
	char* p;
	String query, varname, value;
	int i, j, l;

	if ( ( p = std::getenv ("QUERY_STRING") ) != NULL )
	{
		query = p;

		do {
			l = query.find ("=",i);
			j = query.find ("&",l);
			varname = query.substr (i, l-i);
			value = query.substr (l+1, j-(l+1));
			i = j+1;
			this->GET[varname] = value;
		} while ( j != -1 );
	}
}

//Method to save POST requests
void blym::get_POST ()
{
	int len;
	char* p;
	String query, varname, value;
	int i, j, l;

	if (std::sscanf ( (char*) std::getenv ("CONTENT_LENGTH"), "%d", &len ) == 1 )
	{
		p = new char [len];
		fgets (p, len, stdin);
		query = p;
		delete[] p;

		do {
			l = query.find ("=",i);
			j = query.find ("&",l);
			varname = query.substr (i, l-i);
			value = query.substr (l+1, j-(l+1));
			i = j+1;
			this->POST[varname] = value;
		} while ( j != -1 );
	}
}
void blym::get_COOKIE ()
{
	char* p;
	String query, varname, value;
	int i, j, l;

	if ( ( p = std::getenv ("HTTP_COOKIE") ) != NULL )
	{
		query = p;

		do {
			l = query.find ("=",i);
			j = query.find (";",l);
			varname = query.substr (i, l-i);
			value = query.substr (l+1, j-(l+1));
			i = j+1;
			this->COOKIE[varname] = value;
		} while ( j != -1 );
	}
}



//Usage
//std::map<String, String> newCookie;
//newCookie['name'] = "value";
//blym::setcookie (newCookie);
void blym::setcookie (std::map<String, String>& myCookie)
{
	std::map<String, String>::iterator it;
	for (myCookie.begin (); it != myCookie.end (); it++)
	{
		*this << "Set-Cookie:" << (*it).first << "=" << (*it).second << ";\n";
	}
	this->get_COOKIE();
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
		curl_easy_setopt (ch, CURLOPT_WRITEFUNCTION, this->save_data); 
		curl_easy_setopt (ch, CURLOPT_WRITEDATA,&content);
		curl_easy_perform (ch);
		curl_easy_cleanup (ch);
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

String blym::sql_escape (String query)
{
	String keys[] = {"INSERT", "AND", "UNION", "SELECT", "CONCAT", "/", "+", " ", "'", "\"\""};
	for (int i=0; i<= (sizeof (keys) / sizeof (String)); i++)  {
		if (query.find (keys[i]) != String::npos)
			return query.erase (query.find (keys[i]));
		else
			continue; 
	}
 	return query; 
}

bool blym::is_set (String to_check)
{
	return (to_check.length ()) ? true : false;
}

