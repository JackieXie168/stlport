#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>

#ifdef MAIN 
#define minus_test main
#endif
#endif
int minus_test(int, char**)
{
  cout<<"Results of minus_test:"<<endl;
int input1 [4] = { 1, 5, 7, 8 };
int input2 [4] = { 1, 4, 8, 3 };

  int output [4];
  transform((int*)input1, (int*)input1 + 4, (int*)input2, (int*)output, minus<int>());
  for(int i = 0; i < 4; i++)
    cout << output[i] << endl;
  return 0;
}
