#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>

#include "fadapter.h"

#ifdef MAIN 
#define foreach1_test main
#endif
#endif
static void print_sqr(int a_)
{
  cout << a_ * a_ << " ";
}
int foreach1_test(int, char**)
{
  cout<<"Results of foreach1_test:"<<endl;

  vector <int> v1(10);
  for(int i = 0; i < v1.size(); i++)
    v1[i] = i;
  for_each(v1.begin(), v1.end(), ptr_proc(print_sqr) );
  cout << endl;
  return 0;
}
