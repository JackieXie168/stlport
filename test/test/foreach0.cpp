#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#include "fadapter.h"

#ifdef MAIN 
#define foreach0_test main
#endif
#endif
static void print(int a_)
{
  cout << a_ << ' ';
}
int foreach0_test(int, char**)
{
  cout<<"Results of foreach0_test:"<<endl;

int numbers[10] = { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55 };

  for_each(numbers, numbers + 10, ptr_proc(print));
  cout << endl;
  return 0;
}
