#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define unique1_test main
#endif
#endif
int unique1_test(int, char**)
{
  cout<<"Results of unique1_test:"<<endl;
int numbers[8] = { 0, 1, 1, 2, 2, 2, 3, 4 };

  unique((int*)numbers, (int*)numbers + 8);
  for(int i = 0; i < 8; i ++)
    cout << numbers[i] << ' ';
  cout << endl;
  return 0;
}
