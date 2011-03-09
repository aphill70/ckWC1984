
#ifndef OCCURRENCE_H
#define OCCURRENCE_H

#include <string>
#include <iostream>

#include "Debug.h"
#include "Url.h"

using namespace std;

/* 
 * 
 *
 *
 */
class Occurrence{
private:
  int count;
  string value;
  string url;

public:
  /**
   * Default Constructor
   */
  Occurrence();

  /**
   * Constructor that takes a string url and a word
   * and sets the url and word values and sets the
   * count to 1
   */
  Occurrence(string site, string word);

  /**
   * Destructor
   * 
   */
  ~Occurrence();
  
  /**
   * Gets the Count
   * 
   * Returns number of times this word has
   * been seen.
   * 
   * @return int number of times word seen
   */
  int getCount();
  
  /**
   * get word value
   * 
   * Gets the string value of the word
   * that this occurrence represents
   * 
   * @return the string value of the word
   */
  string getValue();
  
  /**
   * Get the site this Occurrence is tracking
   */
  string getSite();
  
  /**
   * increments the count of this occurrence
   */
  void incrementCount();
  
};
#endif