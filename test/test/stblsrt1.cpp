#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <defalloc.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define stblsrt1_test main
#endif
#endif
int stblsrt1_test(int, char**)
{
  cout<<"Results of stblsrt1_test:"<<endl;
int array[6] = { 1, 50, -10, 11, 42, 19 };

  stable_sort(array, array + 6);
  for(int i = 0; i < 6; i++)
    cout << array[i] << ' ';
  cout << endl;
  return 0;
}
