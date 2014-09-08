#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>

#ifdef MAIN 
#define modulus_test main
#endif
#endif
int modulus_test(int, char**)
{
  cout<<"Results of modulus_test:"<<endl;
int input1 [4] = { 6, 8, 10, 2 };
int input2 [4] = { 4, 2, 11, 3 };

  int output [4];
  transform((int*)input1, (int*)input1 + 4, (int*)input2, (int*)output, modulus<int>());
  for(int i = 0; i < 4; i++)
    cout << output[i] << endl;
  return 0;
}
