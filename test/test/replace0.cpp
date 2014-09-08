#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define replace0_test main
#endif
#endif
int replace0_test(int, char**)
{
  cout<<"Results of replace0_test:"<<endl;
int numbers[6] = { 0, 1, 2, 0, 1, 2 };

  replace(numbers, numbers + 6, 2, 42);
  for(int i = 0; i < 6; i++)
    cout << numbers[i] << ' ';
  cout << endl;
  return 0;
}
