#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>

#ifdef MAIN 
#define greater_test main
#endif
#endif
int greater_test(int, char**)
{
  cout<<"Results of greater_test:"<<endl;
int array [4] = { 3, 1, 4, 2 };

  sort(array, array + 4, greater<int>());
  for(int i = 0; i < 4; i++)
    cout << array[i] << endl;
  return 0;
}
