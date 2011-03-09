#include <iostream>
#include <string>

#include "StopWords.h"
#include "Url.h"
#include "PageDownloader.h"
#include "URLInputStream.h"
#include "Page.h"
#include "HTMLParser.h"

void TestStopWords();
bool TestStopWordsFind(StopWords* stopWords, string wordFile);

void TestUrl();
bool TestUrlString();
bool TestUrlResolver();

void TestPageDownloader();
bool TestPageDownloaderUrl();

void TestHTMLParser();
bool TestHTMLParserConstructor();

void PrintTestResults(bool results);
void PrintErrorReport();

string errors[128];
int errorcount = 0;
const string delim = "########################";
using namespace std;

int main(int argc, char * argv[]){
    
  TestStopWords();
    
  TestUrl();
  
  TestPageDownloader();
  
  TestHTMLParser();
}

void TestHTMLParser(){
  cout << delim << "## Testing HTMLParser ##" << delim << endl;

  cout << "  HTMLParser Constructor. . . . .";
  
  PrintTestResults(TestHTMLParserConstructor());

}

bool TestHTMLParserConstructor(){
  /* http://students.cs.byu.edu/~cs240ta/winter2011/projects/crawler/ - 7880
   * http://www.cksuperman.com/test.html - 8504
   * 
   */
  HTMLParser parser;
  
  string testParser[5] = {"http://students.cs.byu.edu/~cs240ta/winter2011/projects/crawler/", "http://www.cksuperman.com/test.html"};
  
  int parserans[5] = {7880, 8504};
  
  for(int i = 0; i < 2; i++){
    parser.runParser(testParser[i]);
    
    if(parser.getWordCount() != parserans[i])
      errors[errorcount++] = "Expected word count Did not equal Actual Word Count";
  }
  

  return (errorcount == 0);
}



void TestPageDownloader(){
  cout << delim << " Testing PageDownloader " << delim << endl;

  cout << "  PageDownloader Constructor. . .";
  
  PrintTestResults(TestPageDownloaderUrl());

}

bool TestPageDownloaderUrl(){
  string testPageUrl[5] = {"http://www.cksuperman.com", "http://www.cksuperman.com/test.html", "file:///user/home/chris/cs240/test/inputFile.html"};
  
  for(int i = 0; i < 3; i++){
    Url* testUrl = new Url(testPageUrl[i]);
    delete testUrl;
  }
  
  return (errorcount == 0);
}

void TestUrl(){
  cout << delim << "##### Testing URL ######" << delim << endl;
  
  cout << "  String Constructor. . . . . . .";
  PrintTestResults(TestUrlString());
  
  cout << "  Resolve URL . . . . . . . . . .";
  PrintTestResults(TestUrlResolver());

}

bool TestUrlResolver(){
  Url * url = new Url("http://www.google.com/path/to/here");
  
  string resolverTest[5] = {"./././../test#gohere", 
			    "../../test?gohere", 
			    "./././../../meHere",
			    "http://www.cksuperman.com/cs240Test.html#test"};
  
  string resolverAns[5] = {"http://www.google.com/path/test#gohere", 
			    "http://www.google.com/test?gohere", 
			    "http://www.google.com/meHere",
			    "http://www.cksuperman.com/cs240Test.html"};
			    
  string resolverPath[5] = {"/path/test",
			    "/test",
			    "/meHere"};

  Url * DownloadUrl = new Url(resolverTest[3]);
  

  if(DownloadUrl->getShortUrl().compare(resolverAns[3]) != 0)
    errors[errorcount++] = "URL should have been " + resolverAns[3] + " was " + DownloadUrl->getShortUrl();
  
  for(int i = 0; i < 3; i++){
    Url* testUrl = url->resolveUrl(resolverTest[i]);
    
    if(testUrl->getUrl().compare(resolverAns[i]) != 0)
      errors[errorcount++] = "URL should have been " + resolverAns[i] + " was " + testUrl->getUrl();

    if(testUrl->getPath().compare(resolverPath[i]) != 0)
      errors[errorcount++] = "URL should have been " + resolverPath[i] + " was " + testUrl->getPath();
    
    delete testUrl;
  }
  delete url;
  delete DownloadUrl;
  return (errorcount == 0);
}

bool TestUrlString(){
  string urloptions[10] = {"http://www.google.com", 
			   "http://www.google.com/", 
			   "http://www.google.com/path/to/here#here", 
			   "file:///path/to/here/is/this.php",
			   "file:///path/to/here/is/this.php?query"};

  for(int i = 0; i < 5; i++){
    Url * url = new Url(urloptions[i]);

    if(urloptions[i] != url->getUrl())
      errors[errorcount++] = "The URL should be " + urloptions[i] + " Should Be " + url->getUrl();
    
    delete url;
  }
  
  return (errorcount == 0);
}

void TestStopWords(){
  cout << delim << "## Testing StopWords ###" << delim << endl;
  string testFile[5] = {"test/input/stopword.txt", "test/input/stopword2.txt"};
  
  for(int i = 0; i < 2; i++){
    cout << "  Starting File Load Test . . . .";
    StopWords * testStop = new StopWords(testFile[i]);

    PrintTestResults(TestStopWordsFind(testStop, testFile[i]));
    delete testStop;
  }
}

bool TestStopWordsFind(StopWords* stopWords, string wordFile){
  ifstream file;
  file.open(wordFile.c_str());
  
  if (!file.is_open()){
    cout << "Unable to open file: " << wordFile << endl;
    return -2;
  }
  char curLine[1024];
  while (file.getline(curLine, sizeof(curLine))){
    string curLineCopy(curLine);
    
    if(!stopWords->contains(curLineCopy))
      errors[errorcount++] = "StopWord array Should Contain: " + curLineCopy;      

    curLine[0] = toupper(curLine[0]);
    string curLineCopyUpper(curLine);
    
    if(!stopWords->contains(curLineCopyUpper))
      errors[errorcount++] = "StopWord array Should Contain: " + curLineCopyUpper;      
  }
  
  file.close();
  
  string dneWords[10] = {"Yahoo", "Borders", "Pizza", "Apple", "Pineapple", "Peanut"};
  
  for(int i = 0; i < 6; i++){
  
    if(stopWords->contains(dneWords[i])){
      errors[errorcount++] = "StopWords Should Not Contain: " + dneWords[i];
    }
  }
  return (errorcount == 0);
}

void PrintTestResults(bool results){
  if(results)
    cout << " . . . . . . . . . . . . .Test Passed" << endl;
  else{
    cout << " . . . . . . . . . . . . .Test Failed" << endl;
  
    PrintErrorReport();
  }
}

void PrintErrorReport(){
  for(int i = 0; i < errorcount; i++){
    cout << errors[i] << endl;
  }
  
  errorcount = 0;
  
}



