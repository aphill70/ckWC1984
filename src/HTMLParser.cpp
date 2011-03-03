#include "HTMLParser.h"
#include <iostream>

using namespace std;

HTMLParser::HTMLParser():inputStream(NULL), title(""){
  return;
}
  
HTMLParser::~HTMLParser(){
  
  if(inputStream != NULL){
    
    if(inputStream->IsOpen())
      inputStream->Close();
  
    delete inputStream;
    inputStream = NULL;
  }
}

void HTMLParser::parseHTML(string url){

  try{
    inputStream = new URLInputStream(url);
    
    
    HTMLTokenizer * tokenizer = new HTMLTokenizer(inputStream);
    
    while(tokenizer->HasNextToken()){
      HTMLToken curToken = tokenizer->GetNextToken();
     
      if(curToken.GetType() == TAG_START){
	cout << "<" << curToken.GetValue() << ">" << endl;
	if(curToken.GetValue() == "head")
	  processHead(*tokenizer);
      
      }else if(curToken.GetType() == TEXT && !isWhiteSpace(curToken.GetValue())){
	cout << curToken.GetValue() << endl;
      }
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

void HTMLParser::processHead(HTMLTokenizer & tokenizer){
 
  while(tokenizer.HasNextToken()){
    HTMLToken headToken = tokenizer.GetNextToken();
    
    if(headToken.GetType() == TAG_END && headToken.GetValue().compare("head") == 0){
      cout << "</" << headToken.GetValue() << ">" << endl;
      break;
    }
    
    if(headToken.GetType() == TAG_START && headToken.GetValue() == "title")
      processTitle(tokenizer);
  }
}

void HTMLParser::processTitle(HTMLTokenizer & tokenizer){
  HTMLToken titleToken = tokenizer.GetNextToken();
  if(titleToken.GetType() != TAG_END){
     cout << titleToken.GetValue() << endl;
//      title = titleToken.GetValue();
     cout << title; 
      
//     description = title;
//     description.assign(titleToken.GetValue());
  }
}
