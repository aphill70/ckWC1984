#include "PrintXml.h"

using namespace std;

PrintXml::PrintXml(KeyWordIndex* index, PageHistory* history, string name, string start){
  file.open(name.c_str());;
  keyindex = index;
  pghistory = history;
  startUrl = start;
}

PrintXml::~PrintXml(){
  
}

void PrintXml::PrintWebsite(){
  
  file << "<website>\n";
    PrintStartUrl();
    PrintPageHistory();
    PrintKeyWordIndex();
  file << "</website>\n";
  
  file.close();
  
}

void PrintXml::PrintStartUrl(){
  StringUtil::EncodeToXml(startUrl);
  file << "\t<start-url>\n";
  file << "\t" << startUrl << "\n";
  file << "\t</start-url>\n";
}

void PrintXml::PrintPageHistory(){
  file << "\t<pages>\n";
  
  PrintPage();
  
  file << "\t</pages>\n";
}

void PrintXml::PrintPage(){
  pghistory->IteratorInit();
  
  while(pghistory->HasNext()){
    Page * curpg = pghistory->Next();
    
    string url = curpg->getUrl()->getShortUrl();
    StringUtil::EncodeToXml(url);
    
    string title = curpg->getTitle();
    StringUtil::EncodeToXml(title);
    
    file << "\t\t<page>\n";
      file << "\t\t\t<url>\n";
      file << "\t\t\t" << url << "\n";
      file << "\t\t\t</url>" << "\n";
      file << "\t\t\t<description>" << title << "</description>\n";
    file << "\t\t</page>\n";
  }
}

void PrintXml::PrintKeyWordIndex(){
  file << "\t<index>\n";
  
  PrintKeyWord();
  
  file << "\t</index>\n";
}

void PrintXml::PrintKeyWord(){
  keyindex->KeyWordIteratorInit();
  
  while(keyindex->KeyWordIteratorHasNext()){
    KeyWordNode * curnode = keyindex->KeyWordIteratorNext();
    
    string value = curnode->GetValue();
    StringUtil::EncodeToXml(value);
    
      file << "\t\t<word>\n";
	file << "\t\t\t<value>" << value << "</value>\n";
      
	PrintOccurrenceSet(curnode->GetSet());
      file << "\t\t</word>\n";
  }
}

void PrintXml::PrintOccurrenceSet(OccurrenceSet * set){
  set->IteratorInit();
  while(set->HasNext()){
    OccurrenceNode * occ = set->Next();
    
    int count = occ->getCount();
    
    string value = occ->GetValue();
    StringUtil::EncodeToXml(value);
    
    file << "\t\t\t<occurrence>\n";
      file << "\t\t\t\t<url>\n";
      file << "\t\t\t\t" << value << "\n";
      file << "\t\t\t\t</url>" << "\n";
      file << "\t\t\t\t<count>" << count << "</count>\n";
    file << "\t\t\t</occurrence>\n";
  }

}