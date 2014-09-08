#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>

#ifdef MAIN 
#define lesseq_test main
#endif
#endif
int lesseq_test(int, char**)
{
  cout<<"Results of lesseq_test:"<<endl;
int array [4] = { 3, 1, 4, 2 };

  sort(array, array + 4, less_equal<int>());
  for(int i = 0; i < 4; i++)
    cout << array[i] << endl;
  return 0;
}
