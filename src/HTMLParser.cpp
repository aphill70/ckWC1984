#include "HTMLParser.h"
#include <iostream>

using namespace std;

HTMLParser::HTMLParser(){
  inputStream = NULL;
  title = "";
  arraysize = 64;
  linkarraysize = 64;
  words = new string[arraysize];
  links = new string[linkarraysize];
  wordcount = 0;
  linkcount = 0;
  return;
}
  
HTMLParser::~HTMLParser(){
  
  if(inputStream != NULL){
    
    if(inputStream->IsOpen())
      inputStream->Close();
  
    delete inputStream;
    inputStream = NULL;    
  }
    delete [] words;
    words = NULL;
    
    title = "";
    arraysize = 0;
    wordcount = 0;
}

int HTMLParser::getWordCount(){
  return wordcount;
}

int HTMLParser::getLinkCount(){
  return linkcount;
}

void HTMLParser::runParser(string url){
  try{
    inputStream = new URLInputStream(url);
    
    HTMLTokenizer * tokenizer = new HTMLTokenizer(inputStream);
    
    while(tokenizer->HasNextToken()){
      HTMLToken curToken = tokenizer->GetNextToken();
     
      if(isHTMLStart(curToken))
	  processHtml(*tokenizer);
    }

  delete tokenizer;
    
  }
  catch (std::exception &e){
    cout << "Exception Occurred:" << e.what() << endl;
  }
  catch (CS240Exception &e){
    cout << "Exception Occurred:" << e.GetMessage() << endl;
  }
  catch (...){
    cout << "Unknown Exception Occurred" << endl;
  }

}

bool HTMLParser::isWhiteSpace(string token){
  const char * p = token.c_str();
  
  while(isspace(*p)){
   p++; 
  }
  
  if(*p == '\0')
    return true;
  else
    return false;  
}


void HTMLParser::processHtml(HTMLTokenizer & tokenizer){

  while(tokenizer.HasNextToken()){

    HTMLToken curToken = tokenizer.GetNextToken();
  
    if(isHeadStart(curToken)){
	processHead(tokenizer);
    }else if(isText(curToken)){
      string tmpstr = curToken.GetValue();

      processText(tmpstr);
    }else if(isLinkStart(curToken))
      processLink(curToken);
  }  
}

void HTMLParser::processHead(HTMLTokenizer & tokenizer){
 
  while(tokenizer.HasNextToken()){
    
    HTMLToken headToken = tokenizer.GetNextToken();
    
    if(headToken.GetType() == TAG_END && headToken.GetValue().compare("head") == 0)
      return;
    
    if(isTitleStart(headToken))
      processTitle(tokenizer);

  }// End While Loop
}

void HTMLParser::processTitle(HTMLTokenizer & tokenizer){
  HTMLToken titleToken = tokenizer.GetNextToken();
  if(titleToken.GetType() != TAG_END)
    title = titleToken.GetValue();
}

void HTMLParser::processText(string text){
      StringUtil::ToLower(text);
      StringUtil::Trim(text);
      
	string exp = "[a-zA-Z][a-zA-Z0-9_-]*";
	const int MATCH = 0;
	
	boost::regex re(exp, boost::regex_constants::icase);

 	boost::sregex_token_iterator finder(text.begin(), text.end(), re, MATCH);
 	boost::sregex_token_iterator no_match;

 	while(finder != no_match)
 	{
 		//This is one way of getting the token
 		string regtok(*finder);
		words[wordcount++] = regtok;
		
 		
//  		cout << "\"" << regtok << "\"" << endl;
 		*finder++; //Move to the next token, or to no_match state
 		
 		if(wordcount == arraysize)
		  growArray();
 	}
//  	cout << wordcount << endl;
}

void HTMLParser::processLink(HTMLToken & token){
  
  if(token.AttributeExists("href") && !isFragment(token.GetAttribute("href"))){
    links[linkcount++] = token.GetAttribute("href");
    if(linkcount == linkarraysize)
      growLinkArray();
  }
}

bool HTMLParser::isHeadStart(HTMLToken & token){

  return (token.GetType() == TAG_START && token.GetValue() == "head");
}

bool HTMLParser::isHTMLStart(HTMLToken & token){
  return (token.GetType() == TAG_START && token.GetValue() == "html");  
}

bool HTMLParser::isTitleStart(HTMLToken & token){
  return (token.GetType() == TAG_START && token.GetValue() == "title");
}

bool HTMLParser::isText(HTMLToken & token){
  return (token.GetType() == TEXT && !isWhiteSpace(token.GetValue()));
}

bool HTMLParser::isLinkStart(HTMLToken & token){
  return (token.GetType() == TAG_START && token.GetValue() == "a");  
}

bool HTMLParser::isFragment(string link){
	boost::regex re("#[ a-zA-Z0-9_-]*");
	return (boost::regex_match(link, re));
}


void HTMLParser::growArray(){
  int tmpsize = arraysize * 2;
  
  string* tmparray = new string[tmpsize];
  
  for(int i = 0; i < wordcount; i++){
    string stringCopy(words[i]);
    tmparray[i] = stringCopy;
  }

  arraysize = tmpsize;
  
  delete [] words;
  words = tmparray;
  
}

void HTMLParser::growLinkArray(){
  int tmpsize = linkarraysize * 2;
  
  string* tmparray = new string[tmpsize];
  
  for(int i = 0; i < linkcount; i++){
    string stringCopy(links[i]);
    tmparray[i] = stringCopy;
  }

  linkarraysize = tmpsize;
  
  delete [] links;
  links = tmparray;
}
