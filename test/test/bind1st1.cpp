#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>

#ifdef MAIN 
#define bind1st1_test main
#endif
#endif
int bind1st1_test(int, char**)
{
  cout<<"Results of bind1st1_test:"<<endl;
  int array [3] = { 1, 2, 3 };
  int* p = remove_if((int*)array, (int*)array + 3, 
    bind1st(less<int>(), 2));
  for(int* i = array; i != p; i++)
    cout << *i << endl;
  return 0;
}
