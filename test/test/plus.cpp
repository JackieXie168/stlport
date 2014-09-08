#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>

#ifdef MAIN 
#define plus_test main
#endif
#endif
int plus_test(int, char**)
{
  cout<<"Results of plus_test:"<<endl;
int input1 [4] = { 1, 6, 11, 8 };
int input2 [4] = { 1, 5, 2, 3 };

  int total = 
    inner_product(input1, input1 + 4, input2, 0, plus<int>(), multiplies <int>());
  cout << "total = " << total << endl;
  return 0;
}
