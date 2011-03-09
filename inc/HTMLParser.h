
#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <string>
#include <boost/regex.hpp>

#include "URLInputStream.h"
#include "HTMLTokenizer.h"
#include "CS240Exception.h"
#include "StringUtil.h"

using namespace std;

/* 
 * 
 *
 *
 */
class HTMLParser{
private:
  URLInputStream * inputStream;
  string title;
  
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
  
private:
  /**
   * bool isWhiteSpace
   * 
   * test if a Text Token Contains only whitespace
   * 
   * @return true if the line contains only whitespace else false
   */
  bool isWhiteSpace(string token);
  
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
   * Process Title
   * 
   * Processes all the tags and text between the title tags
   * 
   * @parameter HTMLTokenizer - takes an instantiated HTMLTokenizer
   */
  void processTitle(HTMLTokenizer & tokenizer);
  
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
   * isLinkStart
   * 
   * tests if the passed in token is the opening tag of a link
   * 
   * @parameter token - HTMLToken Object to be tested
   * @return bool true if tag is <a> else false
   */  bool isLinkStart(HTMLToken & token);
  
  /**
   * tests the passed in token to see if it is
   * a text token containing text
   */
  bool isText(HTMLToken & token);
  
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
};
#endif
