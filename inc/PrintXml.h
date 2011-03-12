#ifndef PRINTXML_H
#define PRINTXML_H

#include <string>
#include <fstream>
#include <iostream>
#include <ostream>

#include "KeyWordIndex.h"
#include "OccurrenceSet.h"
#include "PageHistory.h"
#include "StringUtil.h"


class PrintXml{
public:
  PrintXml(KeyWordIndex* index, PageHistory* history, string name, string start);
  
  ~PrintXml();
  
  void PrintWebsite();
private:
  ofstream file;
  KeyWordIndex * keyindex;
  PageHistory * pghistory;
  std::string startUrl;
  
  void PrintKeyWordIndex();
  void PrintStartUrl();
  void PrintPageHistory();
  void PrintPage();
  void PrintKeyWord();
  void PrintOccurrenceSet(OccurrenceSet* set);

  
};


#endif
