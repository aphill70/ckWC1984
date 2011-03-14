#include <iostream>
#include <string>

#include "StopWords.h"
#include "Url.h"
#include "URLInputStream.h"
#include "Page.h"
#include "HTMLParser.h"
#include "OccurrenceSet.h"
#include "KeyWordIndex.h"
#include "PageQueue.h"
#include "PageHistory.h"

void TestStopWords();
bool TestStopWordsFind(StopWords* stopWords, string wordFile);

void TestUrl();
bool TestUrlString();
bool TestUrlResolver();

void TestPageDownloader();
bool TestPageDownloaderUrl();

void TestHTMLParser();
bool TestHTMLParserConstructor();

void TestPage();
bool TestPageCreator();

void TestOccurrenceSet();
bool TestOccurrenceSetCreator();

void TestKeyWordIndex();
bool TestKeyWordIndexInput();

void TestPageQueue();
bool TestPageQueueCreation();

void TestPageHistory();
bool TestPageHistoryCreation();

void PrintTestResults(bool results);
void PrintErrorReport();

string errors[128];
int errorcount = 0;
const string delim = "########################";
using namespace std;

int main(int argc, char * argv[]){
    
//   TestStopWords();
    
  TestUrl();
  
//   TestPageDownloader();
  
//   TestHTMLParser();
  
//    TestPage();
  
//   TestOccurrenceSet();
  
//   TestKeyWordIndex();
  
//   TestPageQueue();
  
//   TestPageHistory();
}

void TestPageHistory(){
  cout << delim << "## Testing PageHistory #" << delim << endl;

  cout << "  PageHistory Creation. . . . . .";
  
  PrintTestResults(TestPageHistoryCreation());
}

bool TestPageHistoryCreation(){
  
  PageHistory * history = new PageHistory();
  Url * url = new Url("http://www.cksuperman.com/test.html");
  Page * page = new Page(url);
  
  history->Insert(page);
  
  Url * url4 = new Url("http://www.cksuperman.com/test.html");
  Page * page2 = new Page(url4);
  PageHistoryNode * node;
  node = history->Insert(page2);
  
  if(node != NULL)
    errors[errorcount++] = "Duplicate nodes were inserted";
  
  Url * url2 = new Url("http://www.cksuperman.com/test.html#test");
  
  Page * page3 = new Page(url2);
  
  PageHistoryNode * node2;
  node2 = history->Insert(page3);
  
  if(node2 != NULL)
    errors[errorcount++] = "Duplicate nodes were inserted";
    
  delete history;
  
  return (errorcount == 0);
}


void TestPageQueue(){
  cout << delim << "### Testing PageQueue ##" << delim << endl;

  cout << "  PageQueue Creation. . . . . . .";
  
  PrintTestResults(TestPageQueueCreation());
}

bool TestPageQueueCreation(){
  
  PageQueue * q = new PageQueue();
  
  Url * u = new Url("http://www.cksuperman.com/test.html");
  Page * p = new Page(u);
  q->Insert(p, NULL);
  q->Insert(p, NULL);
  
  if(q->IsEmpty())
    errors[errorcount++] = "The list should not be empty";
  
  cout << q->GetSize() << endl;
  
  while(!q->IsEmpty()){
    cout << q->GetSize();
    
    q->Remove(q->GetFirst());
  }
  
  delete q;
  delete u;
  delete p;
  
  
  return (errorcount == 0);
}


void TestKeyWordIndex(){
  cout << delim << "# Testing KeyWordIndex #" << delim << endl;

  cout << "  KeyWordIndex Creation . . . . .";
  
  PrintTestResults(TestKeyWordIndexInput());

}

bool TestKeyWordIndexInput(){
  KeyWordIndex * index = new KeyWordIndex();
  
  index->Insert("lorem", "http://www.google.com");
  index->Insert("lorem", "http://www.google.com");
  index->Insert("lorem", "http://www.google.com");
  
  index->Insert("lorem", "http://www.gooogle.com/test");
  
  index->Insert("ipsum", "http://www.google.com");
  
  if(index->GetRoot()->GetValue() != "lorem")
    errors[errorcount++] = "Root was incorrect";
  
  if(index->GetSize() != 2)
    errors[errorcount++] = "Size was incorrect";

  if(index->GetRoot()->GetSet()->GetRoot()->GetValue() != "http://www.google.com")
    errors[errorcount++] = "wrong site specified";

  if(index->GetRoot()->GetSet()->GetRoot()->getCount() != 3)
    errors[errorcount++] = "Wrong Number of Occurrences";

  if(index->GetRoot()->GetSet()->GetRoot()->GetRight()->getCount() != 1)
    errors[errorcount++] = "Second Site Wrong Number of Occurrences or site misplaced";
  
  index->KeyWordIteratorInit();
  
  while(index->KeyWordIteratorHasNext()){
    index->KeyWordIteratorNext();
  }
  
  delete index;
  
  return (errorcount == 0);
}

void TestOccurrenceSet(){
  cout << delim << "# Testing OccurenceSet #" << delim << endl;

  cout << "  Occurrence Creation . . . . . .";
  
  PrintTestResults(TestOccurrenceSetCreator());
}

bool TestOccurrenceSetCreator(){
  
  OccurrenceSet * testset = new OccurrenceSet();
  
  testset->setValue("test");
  
  testset->Insert("http://www.google.com");
  testset->Insert("http://www.google.com");
  testset->Insert("http://www.google.com");
  testset->Insert("http://www.google.com");
  testset->Insert("http://www.google.com");
  
  testset->Insert("http://www.google.com/test");
  testset->Insert("http://www.google.com/test");
  testset->Insert("http://www.google.com/test");
  
  if(testset->GetRoot()->getCount() != 5 && testset->GetRoot()->GetRight()->getCount() != 3)
    errors[errorcount++] = "Occurrence count was not 5 or was not 3";
  
  OccurrenceNode * test = testset->Find("http://www.google.com/test");
  
  if(test->getCount() != 3)
    errors[errorcount++] = "Did not find an expected node";
  
  testset->Insert("http://www.google.com/test/another");
  testset->Insert("http://www.google.com/test/another");
  testset->Insert("http://www.google.com/test/another");
  testset->Insert("http://www.google.com/test/another");
  
  testset->Insert("http://www.google.com/test/me");
  
  testset->IteratorInit();
  
  while(testset->HasNext()){
    testset->Next()->getCount();
  }
  
  delete testset;
  return (errorcount == 0);
}



void TestPage(){
  cout << delim << "##### Testing Page #####" << delim << endl;

  cout << "  Page Creation . . . . . . . . .";
  
  PrintTestResults(TestPageCreator());
}

bool TestPageCreator(){
  string testPage[5] = {"http://students.cs.byu.edu/~cs240ta/winter2011/projects/crawler/", "http://www.cksuperman.com/test.html", "file:///home/chris/cs240/test/inputFile.html"};
  
  Url * testurl = new Url(testPage[1]);
  
  Page * testpg = new Page(testurl);
  
  testpg->ExtractData();
  
  testpg->wordIteratorInit();
  
  while(testpg->wordIteratorHasNext()){
    cout << testpg->wordIteratorNext() << endl;
  }
  
  testpg->linkIteratorInit();
  while(testpg->linkIteratorHasNext()){
    cout << testpg->linkIteratorNext() << endl;
  }
  
  delete testpg;
  return (errorcount == 0);
}

void TestHTMLParser(){
  cout << delim << "## Testing HTMLParser ##" << delim << endl;

  cout << "  HTMLParser Constructor. . . . .";
  
  PrintTestResults(TestHTMLParserConstructor());

}

bool TestHTMLParserConstructor(){
  /* http://students.cs.byu.edu/~cs240ta/winter2011/projects/crawler/ - 7882
   * http://www.cksuperman.com/test.html - 624
   * file:///home/chris/cs240/test/inputFile.html - 
   */
  
  string testParser[5] = {"http://students.cs.byu.edu/~cs240ta/winter2011/projects/crawler/", "http://www.cksuperman.com/test.html", "file:///home/chris/cs240/test/inputFile.html"};
  string testDesc[5] = {"Web Crawler", "\nLorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus porttitor faucibus neque, ut interdum magna consequa", "This is a header for testing purposes"};
  
  int parserans[5] = {7882, 624, 8};
  
  for(int i = 0; i < 3; i++){
      HTMLParser parser;
      parser.runParser(testParser[i]);
    
    if(parser.getWordCount() != parserans[i])
      errors[errorcount++] = "Expected word count Did not equal Actual Word Count";
    
    if(parser.getDescription().compare(testDesc[i]) != 0)
      errors[errorcount++] = "DESCRIPTION did not match expected value " + testDesc[i] + "  -  " + parser.getDescription();
    
//      parser.~HTMLParser();
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
  Url * url = new Url("http://www.google.com/path/to/here/");
  
  string resolverTest[5] = {"./././../test#gohere", 
			    "test?gohere", 
			    "/meHere.html",
			    "http://www.cksuperman.com/cs240Test.html"};
  
  string resolverAns[5] = {"http://www.google.com/path/to/test#gohere", 
			    "http://www.google.com/path/to/here/test?gohere", 
			    "http://www.google.com/meHere.html",
			    "http://www.cksuperman.com/cs240Test.html"};
			    
  string resolverPath[5] = {"/path/to/test",
			    "/path/to/here/test",
			    "/meHere.html",
			    "/cs240Test.html"};

  Url * DownloadUrl = new Url(resolverTest[3]);
  

  if(DownloadUrl->getShortUrl().compare(resolverAns[3]) != 0)
    errors[errorcount++] = "URL should have been " + resolverAns[3] + " was " + DownloadUrl->getShortUrl();
  
  for(int i = 0; i < 4; i++){
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
  string urloptions[10] = {"http://www.google.com/", 
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