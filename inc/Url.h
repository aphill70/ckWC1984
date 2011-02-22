
#ifndef URL_H
#define URL_H

#include <string>
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

   public:
   	  // Default Constructor
      Url();

	  // Takes two strings and resolves them into
	  // an actual url
      Url(string absUrl, string relUrl);
      
      Url(string url);

	  // Copy Constructor
      Url(const Url & url);

      // Destructor
      ~Url();
      
      string getUrl();
      
      bool test(ostream & os);
      
   private:
      void resolveUrl(string absUrl, string relUrl);
      
      Url & resolveRelative(string relUrl);



};
#endif
