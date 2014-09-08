#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>

#ifdef MAIN 
#define greateq_test main
#endif
#endif
int greateq_test(int, char**)
{
  cout<<"Results of greateq_test:"<<endl;
int array [4] = { 3, 1, 4, 2 };

  sort(array, array + 4, greater_equal<int>());
  for(int i = 0; i < 4; i++)
    cout << array[i] << endl;
  return 0;
}
