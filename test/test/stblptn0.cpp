#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <defalloc.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define stblptn0_test main
#endif
static bool less_10(int a_)
{
  return a_ < 10 ? 1 : 0;
}
#endif
int stblptn0_test(int, char**)
{
  cout<<"Results of stblptn0_test:"<<endl;

int numbers[6] = { 10, 5, 11, 20, 6, -2 };

  stable_partition((int*)numbers, (int*)numbers + 6, less_10);
  for(int i = 0; i < 6; i++)
    cout << numbers[i] << ' ';
  cout << endl;
  cout.flush();
  return 0;
}
