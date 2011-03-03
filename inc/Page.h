#ifndef PAGE_H
#define PAGE_H

#include <string>
#include "Url.h"
#include "URLInputStream.h"
#include "HTMLTokenizer.h"


using namespace std;

/* PAGE Class
 * Storage class for holding the contents of a page
 * 
 */
class Page{
   private:
   	  // Holds the current pages url
      Url * url;
      // holds the string between <title></title>
      string title;
      // Holds an array of words found in the document
      string words;
      // Holds the word count for iterating over the array
      int totalwords;
      

   public:
   	// Default Constructor
   	Page();

   	// Constructor that takes a string url
   	Page(string url);

   	// takes a url object
   	Page(Url* url);

   	// destructor
   	~Page();

   	string getTitle() const;

   	// Contains the html parser call and loads variables
   	// words, title, links
   	void parsePage();

   	// return the url object contained in page
   	Url getUrl() const;

   	/* Iterator Notes
   	 * Should this be a separate private class?
   	 * How do i implement a private class? friend class?
   	 */

   	// A function to iterate over the array of words
   	// need to track current word and next word
   	// sets needed variables and such so an array can be
   	// iterated over
   	void WordIterator();

   	//checks to see if the array has more words
   	bool wordHasNext();

   	// returns the next string in the array and moves the pointer
   	string wordNext();

   private:
   	// how many words have been iterated over
   	int wordCount;
   	// pointer to next word
   	string * next();

};
#endif
