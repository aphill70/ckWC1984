#include "PageDownloader.h"

using namespace std;

PageDownloader::PageDownloader(){
  
}

PageDownloader::PageDownloader(Url & url){
  
}

PageDownloader::PageDownloader(string url){
    

}

PageDownloader::~PageDownloader(){
  path = "";
  content = "";
  delete inputStream;
}

URLInputStream * PageDownloader::getInputStream(){
  if(inputStream->IsOpen())
    return inputStream;
  else 
    return NULL;
  
}

void PageDownloader::readFile(){
  while (!inputStream->IsDone()){
        content += inputStream->Read();
  }
}