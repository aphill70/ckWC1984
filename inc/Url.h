#ifndef URL_H
#define URL_H

#include <string>

#include <boost/regex.hpp>
using namespace std;

/* URL Class
 * This class will handle url's
 * There will be a constructor 
 * to handle resolving relative urls
 *
 *
 */
class Url{
   private:
     string scheme;
     string location;
     string path;
     string query;
     string fragment;

   public:
     /**
      * Default Constructor
      * Initializes the URL to 
      * NULL
      * 
      */
     Url();

     
     /**
      * String Constructor
      * Takes a url in string form and 
      * converts to a url type
      * 
      * @param url a string parameter
      */
     Url(string url);

     /**
      * Copy Constructor
      * Creates a copy of the passed in URL 
      * object
      * 
      * @param url a Url object
      */ 
     Url(const Url & url);

     /**
      * URL Destructor
      * Destroys the URL object
      */
     ~Url();
     
     /**
      * Getter for the scheme of the urls
      * Return the scheme of the url in string format
      * 
      */
     string getScheme();
      
     /**
      * Getter for the net_location of the urls
      * returns the net location part of the urls
      * for file:// location will be blank
      */ 
     string getLocation();
      
     /**
      * Getter for the path of the urls
      * returns the path of the current url
      * may return blank if the url is the 
      * root of a website
      */
     string getPath();
      
     /**
      * Getter for optional query part
      * may return empty if there is 
      * not a query present in the url
      */
     string getQuery();
      
     /**
      * 
      * 
      */
     string getFragment();
	
     /**
      * 
      * 
      * 
      */
     string getUrl();
     
     /**
      * 
      * 
      */
     string getShortUrl();
      
     /**
      * 
      * 
      */
     Url * resolveUrl(string relUrl);

     /**
      * 
      */
     bool test(ostream & os);
};
#endif
