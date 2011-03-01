#include "Page.h"

using namespace std;

/**
 * 
 * 
 */
Page::page();

/**
 * 
 * 
 */
Page::page(Url& url){
  page = url;
}

/**
 * 
 * 
 */
Page::~page();

/**
 * 
 * 
 */
string Page::getTitle() const;

/**
 * 
 * 
 */
void Page::parsePage();

/**
 * 
 * 
 */
url Page::getUrl() const;

/**
 * 
 * 
 */
void Page::WordIterator();

/**
 * 
 * 
 */
bool Page::wordHasNext();

/**
 * 
 * 
 */
string Page::wordNext();

/**
 * 
 * 
 */
int Page::wordCount;

/**
 * 
 * 
 */
string * Page::next();