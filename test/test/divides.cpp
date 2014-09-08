#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>

#ifdef MAIN 
#define divides_test main
#endif
#endif
int divides_test(int, char**)
{
  cout<<"Results of divides_test:"<<endl;
int input [3] = { 2, 3, 4 };

  int result = accumulate(input, input + 3, 48, divides<int>());
  cout << "result = " << result << endl;
  return 0;
}
