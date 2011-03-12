
#ifndef WEBCRAWLER_H
#define WEBCRAWLER_H

#include <string>
#include <boost/regex.hpp>

#include "StopWords.h"
#include "Url.h"
#include "PageHistory.h"
#include "PageQueue.h"
#include "KeyWordIndex.h"
#include "StringUtil.h"
#include "PrintXml.h"


using namespace std;

/* Class
 * 
 * 
 * 
 *
 *
 */
class WebCrawler{
   private:
      Url * starturl;
      StopWords * stopwords;
      string output;
      PageHistory * history;
      PageQueue * queue;
      KeyWordIndex * index;
   public:
   	// Default Constructor
   	WebCrawler();
   	// Constructor using Command Line arguments
   	WebCrawler(string url, string filestop, string out);
   	// Destructor
   	~WebCrawler();
   	// Function containing main crawling algrithm
   	void CrawlWeb();
	
   private:
	bool IsInScope(Url* s);
	
	bool IsHtml(Url* p);


};
#endif
