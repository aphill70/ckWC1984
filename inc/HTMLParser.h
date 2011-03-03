
#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <string>
#include "URLInputStream.h"
#include "HTMLTokenizer.h"
#include "CS240Exception.h"

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

public:
  /**
   * Default Constructor
   * 
   */
  HTMLParser();
  
  /**
   * 
   * 
   */
  ~HTMLParser();
  
  /**
   * 
   * 
   */
  void parseHTML(string url);
  
private:
  /**
   * 
   * 
   */
  bool isWhiteSpace(string token);
  
  /**
   * 
   * 
   */
  void processHead(HTMLTokenizer & tokenizer);
  
  /**
   * 
   * 
   */
  void processTitle(HTMLTokenizer & tokenizer);
  
};
#endif
