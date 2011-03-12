#ifndef PAGE_H
#define PAGE_H

#include <string>

#include "Url.h"
#include "HTMLParser.h"

using namespace std;

/* PAGE Class
 * Storage class for holding the contents of a page
 * 
 */
class Page{
   private:
      Url * url;
      string title;
      
      string * words;
      string * links;

      int totalwords;
      int totallinks;
      
      bool failed;
public:

  /**
   * 
   * 
   */
  Page();

  /**
   * 
   * 
   */
  Page(Url* site);

  /**
   * 
   * 
   */
  ~Page();
  
  /**
   * 
   * 
   */
  string getTitle() const;

  /**
   * 
   */
  void parsePage();
  
  /**
   * 
   * 
   */
  void ExtractData();

  /**
   * 
   * 
   */
  Url * getUrl() const;

  /**
   * 
   * 
   */
  void wordIteratorInit();
  
  /**
   * 
   * 
   */
  bool wordIteratorHasNext();

  /**
   * 
   * 
   */
  string wordIteratorNext();
  
  /**
   * 
   */
  void linkIteratorInit();
   
  /**
   * 
   * 
   */
  bool linkIteratorHasNext();
  
  /**
   * 
   * 
   */
  string linkIteratorNext();
  
  /**
   * 
   * 
   */
  bool isBadPage();

private:
  int wordIteration;
  int linkIteration;

};
#endif
