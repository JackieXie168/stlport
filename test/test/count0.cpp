#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define count0_test main
#endif
#endif
int count0_test(int, char**)
{
  cout<<"Results of count0_test:"<<endl;
int numbers[10] = { 1, 2, 4, 1, 2, 4, 1, 2, 4, 1 };

  int result = 0;
  count(numbers, numbers + 10, 1, result);
  cout << "Found " << result << " 1's." << endl;
  return 0;
}
