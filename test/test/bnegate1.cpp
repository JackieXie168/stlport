#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>

#ifdef MAIN 
#define bnegate1_test main
#endif
#endif
int bnegate1_test(int, char**)
{
  cout<<"Results of bnegate1_test:"<<endl;
int array [4] = { 4, 9, 7, 1 };

  sort(array, array + 4, binary_negate<greater<int> >(greater<int>()));
  for(int i = 0; i < 4; i++)
    cout << array[i] << endl;
  return 0;
}
