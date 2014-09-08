#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>

#ifdef MAIN 
#define negate_test main
#endif
#endif
int negate_test(int, char**)
{
  cout<<"Results of negate_test:"<<endl;
int input [3] = { 1, 2, 3 };

  int output[3];
  transform((int*)input, (int*)input + 3, (int*)output, negate<int>());
  for(int i = 0; i < 3; i++)
    cout << output[i] << endl;
  return 0;
}
