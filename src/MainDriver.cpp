#include <iostream>
#include "WebCrawler.h"
#include <string>

using namespace std;

int main(int argc, char * argv[]){
    if(argc != 4){
      cout << "USAGE: crawler <start-url> <output-file> <stopword-file>" << endl;
      return 1;
  }
  
  string start = argv[1];
  string output = argv[2];
  string stop = argv[3];
  
  WebCrawler * crawler = new WebCrawler(start, stop, output);
  
  crawler->CrawlWeb();
  
  delete crawler;
}