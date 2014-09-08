#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>
#include <string.h>

#ifdef MAIN 
#define adjfind2_test main
#endif
#endif
static int equal_length(const char* v1_, const char* v2_)
{
  return ::strlen(v1_) == ::strlen(v2_);
}
int adjfind2_test(int, char**)
{
  cout<<"Results of adjfind2_test:"<<endl;
typedef vector <char*> CStrVector;

char* names[] = { "Brett", "Graham", "Jack", "Mike", "Todd" };

  const int nameCount = sizeof(names)/sizeof(names[0]);
  CStrVector v(nameCount);
  for(int i = 0; i < nameCount; i++)
    v[i] = names[i];
  CStrVector::iterator location;
  location = adjacent_find(v.begin(), v.end(), equal_length);
  if(location != v.end())
    cout
      << "Found two adjacent strings of equal length: "
      << *location
      << " -and- "
      << *(location + 1)
      << endl;
  else
    cout << "Didn't find two adjacent strings of equal length.";
  return 0;
}
