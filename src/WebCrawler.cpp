#include "WebCrawler.h"
// Default Constructor
WebCrawler::WebCrawler():starturl(NULL), stopwords(NULL), output(""), history(NULL), queue(NULL){
  return;
}

// Constructor using Command Line arguments
WebCrawler::WebCrawler(string url, string filestop, string out){
  starturl = new Url(url);
  stopwords = new StopWords(filestop);
  output = out;
  history = new PageHistory();
  queue = new PageQueue();
  index = new KeyWordIndex();
}

// Destructor
WebCrawler::~WebCrawler(){
  delete history;
  history = NULL;

//    delete starturl;
  starturl = NULL;
  
  delete stopwords;
  stopwords = NULL;
  
  output = "";


  delete queue;
  queue = NULL;
  
  delete index;
  index = NULL;
  
}

// Function containing main crawling algrithm
void WebCrawler::CrawlWeb(){
  Page * firstpage = new Page (starturl);
  
  history->Insert(firstpage);
  queue->Insert(firstpage, NULL);
  
  if(queue != NULL){
    while(!queue->IsEmpty()){
      Page * currentPage = queue->GetFirst()->GetValue();
      queue->Remove(queue->GetFirst());
      
      currentPage->ExtractData();

       cout << currentPage->getUrl()->getShortUrl() << endl;
      
      if(currentPage->isBadPage()){
 	cout << "badPage" << endl;
	continue;
      }
      currentPage->wordIteratorInit();
      
      while(currentPage->wordIteratorHasNext()){
	string currentWord = currentPage->wordIteratorNext();
	
	if(!stopwords->contains(currentWord))
	  index->Insert(currentWord, currentPage->getUrl()->getShortUrl());
	
      }
      
      currentPage->linkIteratorInit();
      
      while(currentPage->linkIteratorHasNext()){
	
	string tmplink = currentPage->linkIteratorNext();
	Url * tmrl = currentPage->getUrl()->resolveUrl(tmplink);
// 	cout << tmplink << endl;
// 	cout << tmrl->getShortUrl() << endl;
	if(IsHtml(tmrl) && IsInScope(tmrl)){
// 	cout << tmrl->getShortUrl() << endl;
	  Page * tmpg = new Page(tmrl);
	  
	  if(history->Insert(tmpg) != NULL){
	    queue->Insert(tmpg, NULL);	    
	  }
	}else
	  delete tmrl;
      }
    }
  }
  
  ofstream xmlfile;
  
  xmlfile.open(output.c_str());
  
  PrintXml printer(index, history, output, starturl->getShortUrl());
  
  printer.PrintWebsite();
  
}

bool WebCrawler::IsHtml(Url * p){

  string path = p->getPath();
  
  path = path.substr(path.rfind('/'));


  boost::regex re("/[a-zA-Z1-9_-]*(.html|.htm|.shtml|.cgi|.jsp|.asp|.aspx|.php|.pl|.cfm)");

  if(path.compare("/") == 0){
    return true;
  }else if(path.find(".") == -1){
    return true;
  }else if(boost::regex_match(path, re)){
    return true;
  }
  
  return false;
}

bool WebCrawler::IsInScope(Url * s){
  string startScheme = starturl->getScheme();
  string cmpScheme = s->getScheme();
  
  StringUtil::ToLower(cmpScheme);
  StringUtil::ToLower(startScheme);
  
  if(startScheme.compare(cmpScheme) != 0)
    return false;
  
  string startLocation= starturl->getLocation();
  string cmpLocation = s->getLocation();
  
  StringUtil::ToLower(cmpLocation);
  StringUtil::ToLower(startLocation);
  
  if(startLocation.compare(cmpLocation) != 0)
    return false;

  string startPath = starturl->getPath();
  string cmpPath = s->getPath();
  
  startPath = startPath.substr(0, startPath.rfind('/') + 1);

  if(startPath.length() > cmpPath.length())
    return false;
  
  
  
  string::iterator it;
  it = startPath.begin();
  
  string::iterator itcmp;
  itcmp = cmpPath.begin();
  
  string::iterator end;
  end = startPath.end();
  
  while(it != end){
    if(*it != *itcmp)
      return false;

    itcmp++;
    it++;
  }
  
  return true;
}