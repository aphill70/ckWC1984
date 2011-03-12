
#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <string>
#include <string.h>
#include <iostream>
#include <boost/regex.hpp>
#include <assert.h>

#include "URLInputStream.h"
#include "HTMLTokenizer.h"
#include "CS240Exception.h"
#include "StringUtil.h"
#include "Debug.h"

using namespace std;

/* HTMLParser Class
 * 
 *
 *
 */
class HTMLParser{
private:
  URLInputStream * inputStream;
  
  string title;
  string header;
  string description;
  
  int desriptionlength;
  
  string* words;
  string* links;
  
  int linkarraysize;
  int linkcount;
  int arraysize;
  int wordcount;

public:
  /**
   * Default Constructor
   * 
   */
  HTMLParser();
  
  /**
   * Destructor
   * 
   */
  ~HTMLParser();
  
  /**
   * 
   * 
   * 
   */
  string * getWords();
  
  /**
   * 
   * 
   * 
   */
  string * getLinks();
  
  /**
   * Parse the Page
   * 
   * @parameter url - path to the page to be parsed
   * 
   */
  void runParser(string url);
  
  /**
   * Get the Total Links
   * 
   * @return int Total Links found
   */
  int getLinkCount();
  
  /**
   * Get Count of Found Words
   * 
   * @return int Total Words Found
   */
  int getWordCount();
  
  /**
   * 
   * 
   */
  string getDescription();
  
private:
  /**
   * void processHtml
   * 
   * Process tags and text between html tags
   * 
   * @parameter HTMLTokenizer - takes an instantiated HTMLTokenizer
   */
  void processHtml(HTMLTokenizer & tokenizer);
  
  /**
   * Process Head
   * 
   * Process tags and text between the head tags
   * 
   * @parameter HTMLTokenizer - takes an instantiated HTMLTokenizer
   */
  void processHead(HTMLTokenizer & tokenizer);
  
  /**
   * 
   * 
   */
  void processBody(HTMLTokenizer & tokenizer);
  
  /**
   * 
   * 
   */
  void processScript(HTMLTokenizer & tokenizer);
  
  /**
   * Process Title
   * 
   * Processes all the tags and text between the title tags
   * 
   * @parameter HTMLTokenizer - takes an instantiated HTMLTokenizer
   */
  void processTitle(HTMLTokenizer & tokenizer);
  
  /**
   * function that takes a string of text extracted
   * from a TEXT token and parses it for words and 
   * links
   */
  void processText(string text);
  
  /**
   * the passed in token should be an <a> link
   * START_TAG it then checks it for a if it 
   * is a fragment and loads it into the links
   * array
   */
  void processLink(HTMLToken & token);
  
  /**
   * 
   * 
   * 
   */
  void processHeader(HTMLTokenizer & token);
  
  /**
   * 
   * 
   * 
   */
  bool isScriptStart(HTMLToken & token);
  
  /**
   * 
   * 
   * 
   */
  bool isScriptEnd(HTMLToken & token);

  /**
   * bool isWhiteSpace
   * 
   * test if a Text Token Contains only whitespace
   * 
   * @return true if the line contains only whitespace else false
   */
  bool isWhiteSpace(string token);

  /**
   * isHeadStart
   * 
   * Tests if the passed in token is the opening start tag
   * 
   * @parameter token - an HTMLToken object to be tested
   * @return bool - true if tag is <head> else false
   */
  bool isHeadStart(HTMLToken & token);
  
  /**
   * 
   * 
   * 
   */
  bool isHeadEnd(HTMLToken & token);
 
  /**
   * 
   * 
   * 
   */
  bool headToken(HTMLToken & token);
  /**
   * 
   * 
   * 
   */
  bool isBodyStart(HTMLToken & token);
  
  /**
   * isHTMLStart
   * 
   * test if the passed in token is the opening start tag of HTML
   * 
   * @parameter token - HTMLToken object
   * @return bool if <html> true else false
   */
  bool isHTMLStart(HTMLToken & token);
  
  /**
   * isTitleStart
   * 
   * tests if the passed in token is the opening tag of the title
   * 
   * @parameter token - HTMLToken Object to be tested
   * @return bool true if tag is <title> else false
   */
  bool isTitleStart(HTMLToken & token);
  
  /**
   * 
   * 
   * 
   */
  bool isTitleEnd(HTMLToken & token);
  
  /**
   * isLinkStart
   * 
   * tests if the passed in token is the opening tag of a link
   * 
   * @parameter token - HTMLToken Object to be tested
   * @return bool true if tag is <a> else false
   */  
  bool isLinkStart(HTMLToken & token);
  
  /**
   * tests the passed in token to see if it is
   * a text token containing text
   */
  bool isText(HTMLToken & token);
  
  /**
   * Tests for a header tag i.e. <h1> <h2>...
   * 
   */
  bool isHeaderStart(HTMLToken & token);
  
  /**
   * 
   * 
   * 
   * 
   */
  bool isHeaderEnd(HTMLToken & token);
  
  /**
   * tests if the passed in string is a stand alone
   * fragment that has not url attached to it.
   * i.e. #fragment
   * 
   * @parameter link - string from a url
   * @return bool true if is a fragment else false
   */
  bool isFragment(string link);

  /**
   * When called copies the words array into
   * a new array that is double the size of 
   * the old array and replaces the old array 
   * with the new array
   */
  void growArray();

  /**
   * When called copies the links array into
   * a new array that is double the size of 
   * the old array replaces the old array 
   * with the new array
   */
  void growLinkArray();
  
  /**
   * 
   * 
   */
  void processDescription(string text);
  
  /**
   * 
   * 
   * 
   */
  void descriptionProcesser(string text);
};
#endif
