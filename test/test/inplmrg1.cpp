#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <defalloc.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define inplmrg1_test main
#endif
#endif
int inplmrg1_test(int, char**)
{
  cout<<"Results of inplmrg1_test:"<<endl;
int numbers[6] = { 1, 10, 42, 3, 16, 32 };

  int i;
  for(i = 0; i < 6; i++)
    cout << numbers[i] << ' ';
  cout << endl;
  inplace_merge(numbers, numbers + 3, numbers + 6);
  for(i = 0; i < 6; i++)
    cout << numbers[i] << ' ';
  cout << endl;
  return 0;
}
