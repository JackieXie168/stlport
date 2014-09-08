#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>
#include <string.h>

#ifdef MAIN 
#define max2_test main
#endif
#endif
static bool str_compare(const char* a_, const char* b_)
{
  return ::strcmp(a_, b_) < 0 ? 1 : 0;
}

int max2_test(int, char**)
{
  cout<<"Results of max2_test:"<<endl;

  cout << max((char *)"shoe",(char *)"shine", str_compare) << endl;
  return 0;
}
