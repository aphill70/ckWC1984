#include "Page.h"

using namespace std;

Page::Page():url(NULL), title(""), words(NULL), totalwords(0){
  return;
}

Page::Page(Url * site){
  url = site;
  title = "";
  totalwords = 0;
  totallinks = 0;
  
  words = NULL;
  links = NULL;
}

void Page::ExtractData(){
  HTMLParser parser;
  
  parser.runParser(url->getShortUrl());
  
  title = parser.getDescription();
  
  totalwords = parser.getWordCount();
  totallinks = parser.getLinkCount();
  
  words = new string[totalwords];
  links = new string[totallinks];
  
  string * tmpwrds = parser.getWords();
  string * tmplnks = parser.getLinks();
  
  for(int i = 0; i < totalwords; i++){
    words[i] = tmpwrds[i];
  }
  
  for(int i = 0; i < totallinks; i++){
    links[i] = tmplnks[i];
  }
  
}

Page::~Page(){
  delete [] words;
  words = NULL;
  
  delete [] links;
  links = NULL;
  
   delete url;
   url = NULL;
  
  title.clear();
}

Url * Page::getUrl() const{
  return url;
}

string Page::getTitle() const{
  return title;
}

void Page::wordIteratorInit(){
  wordIteration = 0;
}

bool Page::wordIteratorHasNext(){
  return (wordIteration != totalwords);
}

string Page::wordIteratorNext(){
  string tmpstr(words[wordIteration]);
  wordIteration++;
  return tmpstr;
}

void Page::linkIteratorInit(){
  linkIteration = 0;
}

bool Page::linkIteratorHasNext(){
  return (linkIteration != totallinks);
}

string Page::linkIteratorNext(){
  string tmpstr(links[linkIteration]);
   linkIteration++;
   return tmpstr;
}