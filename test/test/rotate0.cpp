#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define rotate0_test main
#endif
#endif
int rotate0_test(int, char**)
{
  cout<<"Results of rotate0_test:"<<endl;
int numbers[6] = { 0, 1, 2, 3, 4, 5 };

  rotate((int*)numbers, numbers + 3, numbers + 6);
  for(int i = 0; i < 6; i++)
    cout << numbers[i] << ' ';
  cout << endl;
  return 0;
}
