#include "Url.h"
#include <iostream>

using namespace std;
// Default Constructor
Url::Url():path(NULL), location(NULL), scheme(NULL), query(NULL){
  return;
}

Url::Url(string url){
  string::iterator it;
  it = url.begin();
  for(int i = 0; i < 7; i++){
    this->scheme += *it;
    it++;
  }
}

// Destructor
Url::~Url(){
  scheme.clear();
  location.clear();
  path.clear();
  query.clear();
}

string Url::getUrl(){
  return scheme + location + path + query;
}

void Url::resolveUrl(string absUrl, string relUrl){
  
}

bool Url::test(ostream & os){
}