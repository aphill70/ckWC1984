
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
  
  bool fail;
public:
  /**
   * Default Constructor
   * 
   * Initializes the parser with NULL values
   */
  HTMLParser();
  
  /**
   * Destructor
   * 
   * Deletes and frees memory
   */
  ~HTMLParser();
  
  bool isFailedDownload();
  
  /**
   * getWords
   * 
   * @return pointer to the word array
   */
  string * getWords();
  
  /**
   * getLinks
   * 
   * @return pointer to the link array
   */
  string * getLinks();
  
  /**
   * Parse the Page
   * 
   * creates the UrlInputStream and feeds 
   * the stream into a parser that processes the text
   * links headers and title
   * 
   * @parameter url - path to the page to be parsed
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
   * getDescription
   * 
   * @return the correct description for the page
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
   * processBody
   * 
   * @parameter takes an already instantiated tokenizer
   * where the current token is the start body tags then 
   * processes the text and tags within the body
   */
  void processBody(HTMLTokenizer & tokenizer);
  
  /**
   * processScript
   * 
   * processes script tags discarding all text and
   * other content, returns when the end tag is 
   * discovered
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
  void processText(string text, bool desc = false);
  
  /**
   * the passed in token should be an <a> link
   * START_TAG it then checks it for a if it 
   * is a fragment and loads it into the links
   * array
   */
  void processLink(HTMLToken & token);
  
  /**
   * processHeader
   * 
   * handles h[1-9] tags text processing
   * receives the tokenizer with current token
   * is the header start tag
   */
  void processHeader(HTMLTokenizer & token);
  
  /**
   * isScriptStart
   * 
   * @return true if token is a script start tag
   */
  bool isScriptStart(HTMLToken & token);
  
  /**
   * isScriptEnd
   * 
   * @return true if token is a script end tag </script>
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
   * isHeadEnd
   * 
   * Tests if the passed in token is the closing head tag
   * 
   * @parameter token - an HTMLToken object to be tested
   * @return bool - true if tag is </head> else false
   */
  bool isHeadEnd(HTMLToken & token);
   
  /**
   * isBodyStart
   * 
   * @return true if the token is a <body> tag
   */
  bool isBodyStart(HTMLToken & token);

  /**
   * 
   * 
   */
  bool isBodyEnd(HTMLToken & token);
  
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
   * isTitleEnd
   * 
   * tests if the passed in token is the closing tag of the title
   * 
   * @parameter token - HTMLToken Object to be tested
   * @return bool true if tag is </title> else false
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
   */
  bool isHeaderStart(HTMLToken & token);
  
  /**
   * Tests for closing header tag i.e. </h1> </h2>...
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
   * processDescription
   * 
   * Wrapper for description Processer
   */
  void processDescription(string text);
  
  /**
   * DescriptionProcesser
   * 
   * Procsses the first 100 characters for the description
   */
  void descriptionProcesser(string text);
    
};
#endif
