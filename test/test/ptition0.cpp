#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define ptition0_test main
#endif
#endif
static int less_10(int a_)
{
  return a_ < 10 ? 1 : 0;
}

int ptition0_test(int, char**)
{
  cout<<"Results of ptition0_test:"<<endl;
int numbers[6] = { 6, 12, 3, 10, 1, 20 };

  partition((int*)numbers, (int*)numbers + 6, less_10);
  for(int i = 0; i < 6; i++)
    cout << numbers[i] << ' ';
  cout << endl;
  return 0;
}
