#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>

#ifdef MAIN 
#define ptrunf2_test main
#endif
static bool even(int n_)
{
  return(n_ % 2) == 0;
}
#endif
int ptrunf2_test(int, char**)
{
  cout<<"Results of ptrunf2_test:"<<endl;

int array [3] = { 1, 2, 3 };

  int* p = find_if((int*)array, (int*)array + 3, ptr_fun(even));
  if(p != array + 3)
    cout << *p << " is even" << endl;
  return 0;
}
