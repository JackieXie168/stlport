#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <defalloc.h>
#include <algo.h>
#include <iostream.h>
#include <string.h>

#ifdef MAIN 
#define stblsrt2_test main
#endif
static bool string_less(const char* a_, const char* b_)
{
  return ::strcmp(a_, b_) < 0 ? 1 : 0;
}
#endif
int stblsrt2_test(int, char**)
{
  cout<<"Results of stblsrt2_test:"<<endl;

char* letters[6] = {"bb", "aa", "ll", "dd", "qq", "cc" };

  stable_sort(letters, letters + 6, string_less);
  for(int i = 0; i < 6; i++)
    cout << letters[i] << ' ';
  cout << endl;
  return 0;
}
