#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define nthelem0_test main
#endif
#endif
int nthelem0_test(int, char**)
{
  cout<<"Results of nthelem0_test:"<<endl;
int numbers[7] = { 5, 2, 4, 1, 0, 3 ,77};

  nth_element(numbers, numbers + 3, numbers + 6);
  for(int i = 0; i < 6; i++)
    cout << numbers[i] << ' ';
  cout << endl;
  return 0;
}
