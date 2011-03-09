#include "Occurrence.h"

using namespace std;

Occurrence::Occurrence(){
  count = 0;
  value = "";
  url = "";

}

Occurrence::Occurrence(string site, string word){
  url = site;
  value = word;
  count = 1;
}

Occurrence::~Occurrence(){
  url = "";
  value = "";
  count = 0;
}

int Occurrence::getCount(){
  return count;
}

string Occurrence::getValue(){
  return value;
}

string Occurrence::getSite(){
  return url;
}

void Occurrence::incrementCount(){
  count++;
}