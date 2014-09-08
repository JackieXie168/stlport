#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>

#ifdef MAIN 
#define nequal_test main
#endif
#endif
int nequal_test(int, char**)
{
  cout<<"Results of nequal_test:"<<endl;
int input1 [4] = { 1, 7, 2, 2 };
int input2 [4] = { 1, 6, 2, 3 };

  int output [4];
  transform((int*)input1, (int*)input1 + 4, (int*)input2, (int*)output, not_equal_to<int>());
  for(int i = 0; i < 4; i++)
    cout << output[i] << endl;
  return 0;
}
