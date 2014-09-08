#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define iota1_test main
#endif
#endif
int iota1_test(int, char**)
{
  cout<<"Results of iota1_test:"<<endl;
  int numbers[10];
  iota(numbers, numbers + 10, 42);
  for(int i = 0; i < 10; i++)
    cout << numbers[i] << ' ';
  cout << endl;
  return 0;
}
