#include "Url.h"

#include <iostream>

using namespace std;
// Default Constructor
Url::Url():scheme(""),location(""), path(""), query(""), fragment(""){
  return;
}

Url::Url(string url){
  scheme = "";
  location = "";
  path = "";
  query = "";
  fragment = "";
  
  string::iterator it;
  it = url.begin();
  for(int i = 0; i < 7; i++){
    this->scheme += *it;
    it++;
  }
  
  while(*it != '/' && it != url.end()){
   this->location += *it;
   it++;
  }
  
  while(it != url.end() && (*it != '?' || *it != '#')){
    if(*it == '#' || *it == '?')
      break;
    this->path += *it;
    it++;
  }
  
  if(*it == '?'){
    while(it != url.end() && *it != '#'){
      this->query += *it;
      it++;
    }
  }

  if(*it == '#'){
    while(it != url.end()){
      this->fragment += *it;
      it++;
    }
  }

  if(path.empty())
    path = "/";
}

// Destructor
Url::~Url(){
  scheme.clear();
  location.clear();
  path.clear();
  query.clear();
  fragment.clear();
}

string Url::getUrl(){
  return scheme + location + path + query + fragment;
}

string Url::getShortUrl(){
  return scheme + location + path + query;
}

string Url::getScheme(){
  return scheme;
}
      
string Url::getLocation(){
  return location;
}
      
string Url::getPath(){
  return path;
}

string Url::getQuery(){
  return query;
}
      
string Url::getFragment(){
  return fragment;
}


Url* Url::resolveUrl(string relUrl){
  
  if(relUrl.find("http://") != -1 || relUrl.find("file://") != -1){
    return new Url(relUrl);
  }
  
  string::iterator it;
  it = relUrl.begin();
  
  string tempurl(path);
  bool firstPass = false;

  if(tempurl.size() - tempurl.rfind('/') != 1)
    tempurl.erase(tempurl.rfind('/'));

  
  while(it != relUrl.end()){
    string temprelUrl(relUrl);
  
    if(isalnum(*it)){
      tempurl += "/";
      while(it != relUrl.end()){
	tempurl += *it;
	it++;
      }
      return new Url(scheme + location + tempurl);
    }
  

    if(*it == '.'){
      it++;
      if(*it == '.'){
	it = it +2;
	tempurl.erase(tempurl.rfind('/'));
	  
      }else{
	it++;
	temprelUrl.erase(temprelUrl.find('/'));
	continue;
      }
    }else if(*it == '/'){
      it++;
    }else{
      if(!firstPass)
	tempurl.append("/");
      firstPass = true;
      tempurl += *it;
      it++;
    }
  }
  return new Url(scheme + location + tempurl);
}