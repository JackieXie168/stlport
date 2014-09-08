#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define uniqcpy1_test main
#endif
#endif
int uniqcpy1_test(int, char**)
{
  cout<<"Results of uniqcpy1_test:"<<endl;
int numbers[8] = { 0, 1, 1, 2, 2, 2, 3, 4 };
int result[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

  unique_copy((int*)numbers, (int*)numbers + 8, (int*)result);
  for(int i = 0; i < 8; i++)
    cout << result[i] << ' ';
  cout << endl;
  return 0;
}
