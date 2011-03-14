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
  
  string lowrelUrl = relUrl;
  StringUtil::ToLower(lowrelUrl);
  
  if(lowrelUrl.find("http://") != (unsigned int)-1 || 
     lowrelUrl.find("file://") != (unsigned int)-1){
    return new Url(relUrl);
  }
  
  string tmpurl = path;
  
  string output;
  
  tmpurl = tmpurl.substr(0, tmpurl.rfind('/'));
  
  string::iterator it;
  
  it = relUrl.begin();
  
  while(it != relUrl.end()){
    
    if(isalnum(*it)){
      
      if(output.empty())
	output = '/';
      while(it != relUrl.end()){
	output += *it;
	it++;
      }
      return new Url(scheme + location + tmpurl + output);
    }else if(*it == '/'){
      while(it != relUrl.end()){
	output += *it;
	it++;
      }
      return new Url(scheme + location + output);
    }else if(*it == '.'){
      it++;
      if(*it == '.'){
	it++;
	tmpurl = tmpurl.substr(0, tmpurl.rfind('/'));
      }
    }
    it++;
  }
  
  
  
  return new Url(scheme + location + output);
}