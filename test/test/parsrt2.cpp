#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>
#include <string.h>

#ifdef MAIN 
#define parsrt2_test main
#endif
static bool str_compare(const char* a_, const char* b_)
{
  return ::strcmp(a_, b_) < 0 ? 1 : 0;
}
#endif
int parsrt2_test(int, char**)
{
  cout<<"Results of parsrt2_test:"<<endl;

char* names[] = { "aa", "ff", "dd", "ee", "cc", "bb" };

  const unsigned nameSize = sizeof(names) / sizeof(names[0]);
  vector <char*> v1(nameSize);
  for(int i = 0; i < v1.size(); i++)
    v1[i] = names[i];
  ostream_iterator<char*> iter(cout, " ");
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  partial_sort(v1.begin(),
                v1.begin() + nameSize / 2,
                v1.end(),
                str_compare);
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  return 0;
}
