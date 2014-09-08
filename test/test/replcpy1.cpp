#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define replcpy1_test main
#endif
#endif
int replcpy1_test(int, char**)
{
  cout<<"Results of replcpy1_test:"<<endl;
int numbers[6] = { 0, 1, 2, 0, 1, 2 };
int result[6] = { 0, 0, 0, 0, 0, 0 };

  replace_copy((int*)numbers, (int*)numbers + 6, (int*)result, 2, 42);
  for(int i = 0; i < 6; i++)
    cout << result[i] << ' ';
  cout << endl;
  return 0;
}
