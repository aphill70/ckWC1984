
#ifndef STOPWORDS_H
#define STOPWORDS_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/* 
 * 
 * 
 * 
 *
 *
 */
class StopWords{
   private:
     int containerSize;
     string* stopwords;
     int lineCount;


   public:
   	  // default constructor
      StopWords();

      // default constructor
      StopWords(string fileName);

      // destructor
      ~StopWords();
      
      int getsize();
      
      // uses bsearch to figure out if the array
      // contains the word or not return 
      bool contains(string word);
      
      bool test(ostream & os);

   private:
      // give the file name for the stop words file
      // loads up the stop words file in an ordered array
      // handles growing the array as needed
      bool loadfile(string fileName);

      void growarray();
      
      //int comparestrs(const void * a, const void * b);
};
#endif
