
#ifndef WEBCRAWLER_H
#define WEBCRAWLER_H

#include <string>
#include "StopWords.h"

using namespace std;

/* PAGE Class
 * 
 * 
 * 
 *
 *
 */
class page{
   private:
      url StartUrl;
      stopwords StopWords;
//      PageHistory pageH;
//test      PageQueue pageQ;

   public:
   	// Default Constructor
   	WebCrawler();
   	// Constructor using Command Line arguments
   	WebCrawler(String url, String filestop);
   	// Destructor
   	~WebCrawler();
   	// Function containing main crawling algrithm
   	CrawlWeb();

   private:


};
#endif
