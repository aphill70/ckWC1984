#include "PageDownloader.h"

using namespace std;

PageDownloader::PageDownloader(){
  
}

PageDownloader::PageDownloader(Url & url){
  
}

PageDownloader::PageDownloader(string url){
  
  string path = url;
  
  
  try{
     
    inputStream = new URLInputStream(url);
  cout << url;

  }catch (std::exception &e){
    
    cout << "Exception Occurred:" << e.what() << endl;
    
  }catch (CS240Exception &e){
	
    cout << "Exception Occurred:" << e.GetMessage() << endl;
    
  }catch (...){
              
    cout << "Unknown Exception Occurred" << endl;
	  
  }

//    path = inputStream->GetLocation();
//    readFile();
//    inputStream->Close();

  
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