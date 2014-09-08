#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>
#include <string.h>

#ifdef MAIN 
#define maxelem2_test main
#endif
static bool str_compare(const char* a_, const char* b_)
{
  return ::strcmp(a_, b_) < 0 ? 1 : 0;
}
#endif
int maxelem2_test(int, char**)
{
  cout<<"Results of maxelem2_test:"<<endl;

char* names[] = { "Brett", "Graham", "Jack", "Mike", "Todd" };

  const unsigned namesCt = sizeof(names)/sizeof(names[0]);
  cout << *max_element((char**)names, (char**)names + namesCt, str_compare) << endl;
  return 0;
}
