#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>
#include "unary.h"

#ifdef MAIN 
#define ucompos2_test main
#endif
#endif
int ucompos2_test(int, char**)
{
  cout<<"Results of ucompos2_test:"<<endl;

int input [3] = { -1, -4, -16 };

  int output [3];
  transform((int*)input, (int*)input + 3, (int*)output, 
    compose1(square_root(), negate<int>()));
  for(int i = 0; i < 3; i++)
   cout << output[i] << endl;
  return 0;
}
