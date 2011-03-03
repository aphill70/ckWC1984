#ifndef PAGEDOWNLOADER_H
#define PAGEDOWNLOADER_H

#include "URLInputStream.h"
#include "CS240Exception.h"
#include "Url.h"

#include <iostream>
#include <string>

using namespace std;

class PageDownloader{
   private:
     URLInputStream * inputStream;
     string path;
     string content;

   public:
      PageDownloader();

      PageDownloader(Url & url);
      
      PageDownloader(string url);

      ~PageDownloader();
      
      URLInputStream * getInputStream();
      
   private:
      void readFile();

};
#endif
