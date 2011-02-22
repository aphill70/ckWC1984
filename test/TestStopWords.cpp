void TestStopWords(){
  cout << delim << " Testing StopWords " << delim << endl;
  string testFile[5] = {"test/stopword.txt", "test/stopword2.txt"};
  
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
