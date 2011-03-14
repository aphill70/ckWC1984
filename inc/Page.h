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
   * Default Constuctor
   * 
   */
  Page();

  /**
   * Constuctor
   * 
   */
  Page(Url* site);

  /**
   * Destuctor
   * 
   */
  ~Page();
  
  /**
   * GetTitle
   * 
   */
  string getTitle() const;

  /**
   * ParsePage
   * 
   * Runs the parser
   */
  void parsePage();
  
  /**
   * 
   * 
   */
  void ExtractData();

  /**
   * Get URL
   * 
   */
  Url * getUrl() const;

  /**
   * Initializes the Word Iterator
   * 
   */
  void wordIteratorInit();
  
  /**
   * Has Next
   * 
   */
  bool wordIteratorHasNext();

  /**
   * Next
   * 
   */
  string wordIteratorNext();
  
  /**
   * Initializes the Link Iterator
   */
  void linkIteratorInit();
   
  /**
   * HasNext
   */
  bool linkIteratorHasNext();
  
  /**
   * Next
   */
  string linkIteratorNext();
  
  /**
   * 
   * @return true if the page is bad threw an
   * exception when downloading
   */
  bool isBadPage();

private:
  int wordIteration;
  int linkIteration;

};
#endif
