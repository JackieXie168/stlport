#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>

#ifdef MAIN 
#define logicor_test main
#endif
#endif
int logicor_test(int, char**)
{
  cout<<"Results of logicor_test:"<<endl;
int input1 [4] = { 1, 1, 0, 1 };
int input2 [4] = { 0, 1, 0, 0 };

  int output [4];
  transform((int*)input1, (int*)input1 + 4, (int*)input2, (int*)output, logical_or<bool>());
  for(int i = 0; i < 4; i++)
    cout << output[i] << endl;
  return 0;
}
