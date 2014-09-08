#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>
#include <string.h>

#ifdef MAIN 
#define min2_test main
#endif
static bool str_compare(const char* a_, const char* b_)
{
  return ::strcmp(a_, b_) < 0 ? 1 : 0;
}
#endif
int min2_test(int, char**)
{
  cout<<"Results of min2_test:"<<endl;

  cout << min((char *)"shoe",(char *)"shine", str_compare) << endl;
  return 0;
}
