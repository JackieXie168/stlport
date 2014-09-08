#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h> 
#include <algo.h>

#ifdef MAIN 
#define bnegate2_test main
#endif
#endif
int bnegate2_test(int, char**)
{
  cout<<"Results of bnegate2_test:"<<endl;
int array [4] = { 4, 9, 7, 1 };

  sort(array, array + 4, not2(greater<int>()));
  for(int i = 0; i < 4; i++)
    cout << array[i] << endl;
  return 0;
}
