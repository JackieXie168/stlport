#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <vector.h>
#include <iostream.h>

#ifdef MAIN 
#define count1_test main
#endif
#endif
int count1_test(int, char**)
{
  cout<<"Results of count1_test:"<<endl;
  vector <int> numbers(100);
  for(int i = 0; i < 100; i++)
    numbers[i] = i % 3;
  int elements = 0;
  count(numbers.begin(), numbers.end(), 2, elements);
  cout << "Found " << elements << " 2's." << endl;
  return 0;
}
