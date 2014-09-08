#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>
#include <string.h>

#ifdef MAIN 
#define inrprod0_test main
#endif
#endif
int inrprod0_test(int, char**)
{
  cout<<"Results of inrprod0_test:"<<endl;
int vector1[5] = { 1, 2, 3, 4, 5 };
int vector2[5] = { 1, 2, 3, 4, 5 };

  int result;
  result = inner_product(vector1, vector1 + 5, vector2, 0);
  cout << "Inner product = " << result << endl;
  return 0;
}
