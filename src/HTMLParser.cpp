#include "HTMLParser.h"

using namespace std;

HTMLParser::HTMLParser(){
  inputStream = NULL;
  title = "";
  header = "";
  description = "";
  
  desriptionlength = 0;
  arraysize = 64;
  linkarraysize = 64;
  
  words = new string[arraysize];
  links = new string[linkarraysize];
  
  wordcount = 0;
  linkcount = 0;
  
  fail = false;
  
  return;
}
  
HTMLParser::~HTMLParser(){
  
/*    if(inputStream->IsOpen())
      inputStream->Close();*/
  
    delete inputStream;
    inputStream = NULL;    

     delete [] words;
    words = NULL;
    
     delete [] links;
    links = NULL;
    
    title = "";
    arraysize = 0;
    wordcount = 0;
}

string * HTMLParser::getWords(){
  return words;
}

string * HTMLParser::getLinks(){
  return links;
}

string HTMLParser::getDescription(){
  if(!title.empty()){
    return title;
  }else if(!header.empty()){
    return header;
  }else{
    return description;
  }
}

int HTMLParser::getWordCount(){
  TRACE(wordcount);
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
  
  inputStream->Close();
  
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

void HTMLParser::processHtml(HTMLTokenizer & tokenizer){
   assert(tokenizer.HasNextToken());

  while(tokenizer.HasNextToken()){

    HTMLToken curToken = tokenizer.GetNextToken();
  
    if(isHeadStart(curToken)){
      TRACE("Head Start");
      processHead(tokenizer);
    }else if(isBodyStart(curToken))
      processBody(tokenizer);
  }  
}

void HTMLParser::processHead(HTMLTokenizer & tokenizer){
  assert(tokenizer.HasNextToken());
 
  while(tokenizer.HasNextToken()){
    HTMLToken headToken = tokenizer.GetNextToken();
    
    if(isHeadEnd(headToken))
      return;
    
    if(isTitleStart(headToken)){
      processTitle(tokenizer);
      TRACE("TITLE Start");
      
    }
  }// End While Loop
}

void HTMLParser::processBody(HTMLTokenizer & tokenizer){
  assert(tokenizer.HasNextToken());
  
  while(tokenizer.HasNextToken()){
    HTMLToken curToken = tokenizer.GetNextToken();
    
    if(isText(curToken)){
      string tmpstr = curToken.GetValue();
      processDescription(tmpstr);
      processText(tmpstr);
    }else if(isLinkStart(curToken))
      processLink(curToken);
    else if(isHeaderStart(curToken) && header.empty()){
	processHeader(tokenizer);
    }else if(isScriptStart(curToken)){
      processScript(tokenizer);
    }else if(isBodyEnd(curToken)){
      return;
    }
    
  }
}

void HTMLParser::processTitle(HTMLTokenizer & tokenizer){
  assert(tokenizer.HasNextToken());
  while(tokenizer.HasNextToken()){
    HTMLToken titleToken = tokenizer.GetNextToken();
    if(titleToken.GetType() == TEXT){
      title += titleToken.GetValue();
      processText(titleToken.GetValue());
    }
    
    if(isTitleEnd(titleToken))
      return;
    
  }
}

void HTMLParser::processHeader(HTMLTokenizer & tokenizer){
  while(tokenizer.HasNextToken()){
    HTMLToken curToken = tokenizer.GetNextToken();
    
    if(isText(curToken)){
      header += curToken.GetValue();
      processText(curToken.GetValue());
    }else if(isHeaderEnd(curToken))
      return;
    else if(isLinkStart(curToken))
      processLink(curToken);
  }
}

void HTMLParser::processText(string text, bool desc){
  assert(!text.empty());
  
  if(desc)
  processDescription(text);
    
  StringUtil::ToLower(text);
  StringUtil::Trim(text);

  string exp = "[a-zA-Z0-9_-]*";
  const int MATCH = 0;

  boost::regex re(exp, boost::regex_constants::icase);

  boost::sregex_token_iterator finder(text.begin(), text.end(), re, MATCH);
  boost::sregex_token_iterator no_match;

  while(finder != no_match){
    string regtok(*finder);

    if(isalpha(regtok[0])){
      words[wordcount++] = regtok;
      TRACE("\"" << regtok << "\"");
    }
    *finder++; //Move to the next token, or to no_match state

    if(wordcount == arraysize)
      growArray();
  }
}

void HTMLParser::processDescription(string text){
  if(desriptionlength != 100)
    descriptionProcesser(text);
  
}

void HTMLParser::processLink(HTMLToken & token){
  if(token.AttributeExists("href") && !isFragment(token.GetAttribute("href"))){
    links[linkcount++] = token.GetAttribute("href");
    if(linkcount == linkarraysize)
      growLinkArray();
  }
}

void HTMLParser::processScript(HTMLTokenizer & tokenizer){

  while(tokenizer.HasNextToken()){
    HTMLToken curToken = tokenizer.GetNextToken();

    if(isScriptEnd(curToken))
      return;
  }
}

void HTMLParser::descriptionProcesser(string text){
  string::iterator p = text.begin();
  while(p < text.end()){
    if(!iswspace(*p) && desriptionlength != 100){
      desriptionlength++;
    }else if(desriptionlength == 100)
      return;
    
    description += *p;
    
    p++;
  }
}

bool HTMLParser::isHeadEnd(HTMLToken & token){
  string lower = token.GetValue();
  StringUtil::ToLower(lower);
  return (token.GetType() == TAG_END && lower.compare("head") == 0);
}

bool HTMLParser::isHeadStart(HTMLToken & token){
  string lower = token.GetValue();
  StringUtil::ToLower(lower);
  return (token.GetType() == TAG_START && lower.compare("head") == 0);
}

bool HTMLParser::isTitleStart(HTMLToken & token){
  string lower = token.GetValue();
  StringUtil::ToLower(lower);
  return (token.GetType() == TAG_START && lower == "title");
}

bool HTMLParser::isTitleEnd(HTMLToken & token){
  string lower = token.GetValue();
  StringUtil::ToLower(lower);
  return (token.GetType() == TAG_END && lower.compare("title") == 0);
}

bool HTMLParser::isBodyStart(HTMLToken & token){
  string lower = token.GetValue();
  StringUtil::ToLower(lower);
  return (token.GetType() == TAG_START && lower == "body");
}

bool HTMLParser::isBodyEnd(HTMLToken & token){
  string lower = token.GetValue();
  StringUtil::ToLower(lower);
  return (token.GetType() == TAG_END && lower == "body");
}

bool HTMLParser::isHTMLStart(HTMLToken & token){
  string lower = token.GetValue();
  StringUtil::ToLower(lower);
  return (token.GetType() == TAG_START && lower == "html");  
}

bool HTMLParser::isText(HTMLToken & token){
  string lower = token.GetValue();
  StringUtil::ToLower(lower);
  return (token.GetType() == TEXT && !isWhiteSpace(lower));
}

bool HTMLParser::isLinkStart(HTMLToken & token){
  string lower = token.GetValue();
  StringUtil::ToLower(lower);
  return (token.GetType() == TAG_START && lower == "a");  
}

bool HTMLParser::isScriptStart(HTMLToken & token){
  string lower = token.GetValue();
  StringUtil::ToLower(lower);
  return (token.GetType() == TAG_START && lower == "script");  
}

bool HTMLParser::isScriptEnd(HTMLToken & token){
  string lower = token.GetValue();
  StringUtil::ToLower(lower);
  return (token.GetType() == TAG_END && lower == "script");    
}

bool HTMLParser::isHeaderStart(HTMLToken & token){
  string lower = token.GetValue();
  StringUtil::ToLower(lower);
	boost::regex re("h[1-9]");
	return (boost::regex_match(lower, re) && token.GetType() == TAG_START);
}
bool HTMLParser::isHeaderEnd(HTMLToken & token){
  string lower = token.GetValue();
  StringUtil::ToLower(lower);
	boost::regex re("[hH][1-9]");
	return (boost::regex_match(lower, re) && token.GetType() == TAG_END);
}

bool HTMLParser::isFragment(string link){
	boost::regex re("^#[ a-zA-Z0-9_-]*");
	return (boost::regex_match(link, re));
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

bool HTMLParser::isFailedDownload(){
  return fail;
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
