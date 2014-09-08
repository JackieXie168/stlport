#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define parsrt0_test main
#endif
#endif
int parsrt0_test(int, char**)
{
  cout<<"Results of parsrt0_test:"<<endl;
int numbers[6] = { 5, 2, 4, 3, 1, 6 };

  partial_sort((int*)numbers, (int*)numbers + 3, (int*)numbers + 6);
  for(int i = 0; i < 6; i++)
    cout << numbers[i] << ' ';
  cout << endl;
  return 0;
}
