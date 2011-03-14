#include <stdlib.h>
#include "StopWords.h"
#include "StringUtil.h"
int comparestrs (const void * a, const void * b);
using namespace std;

//TODO Handle Empty Lines read in;
// default constructor
StopWords::StopWords(){
  
}

StopWords::StopWords(string fileName){
  containerSize = 128;
  stopwords = new string[containerSize];
  
  loadfile(fileName);
}

StopWords::~StopWords(){
  delete [] stopwords;
  lineCount = 0;
  
}

int StopWords::getsize(){
   return lineCount;
}

// give the file name for the stop words file
// loads up the stop words file in an ordered array
// handles growing the array as needed
bool StopWords::loadfile(string fileName){
	ifstream file;
	file.open(fileName.c_str());

	if (!file.is_open()){
		cout << "Unable to open file: " << fileName << endl;
		return -2;
	}

	lineCount = 0;

	char curLine[1024];
	while (file.getline(curLine, sizeof(curLine))){
		string curLineCopy(curLine);
		StringUtil::ToLower(curLineCopy);
		stopwords[lineCount] = curLineCopy;
		++lineCount;
		
		if(lineCount == containerSize){
		  growarray();
		}
	}

	// close file
	//
	file.close();
	return true;
}

void StopWords::growarray(){
  int tmpsize = containerSize * 2;
  
  string* tmparray = new string[tmpsize];
  
  for(int i = 0; i < lineCount; i++){
    string stringCopy(stopwords[i]);
    tmparray[i] = stringCopy;
  }

  containerSize = tmpsize;
  
  delete [] stopwords;
  stopwords = tmparray;
}

bool StopWords::contains(string word){
  string * pItem;
  StringUtil::ToLower(word);
  pItem = (string*) bsearch(&word, stopwords, lineCount, sizeof(string), comparestrs);
  
  return pItem;
}

int comparestrs (const void * a, const void * b){
  string str1 = *(string*) a;
  string str2 = *(string*) b;
  return str1.compare(str2);
}