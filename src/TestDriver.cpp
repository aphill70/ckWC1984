#include <iostream>
#include <string>
#include <string.h>

#include "StopWords.h"
#include "Url.h"

void TestStopWords();
bool TestStopWordsFind(StopWords* stopWords, string wordFile);

void TestUrl();

void PrintTestResults(bool results);
void PrintErrorReport();

string errors[128];
int errorcount = 0;
const string delim = "#########################";
using namespace std;

int main(int argc, char * argv[]){
    TestStopWords();
    
    TestUrl();
    
    
}

void TestUrl(){
  cout << delim << "### Testing URL ###" << delim << endl;
  
  Url * url = new Url("http://www.google.com/");
  
  
}

void TestStopWords(){
  cout << delim << " Testing StopWords " << delim << endl;
  string testFile[5] = {"test/input/stopword.txt", "test/input/stopword2.txt"};
  
  for(int i = 0; i < 2; i++){
    cout << "Starting File Load Test . . . .";
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
  
}



