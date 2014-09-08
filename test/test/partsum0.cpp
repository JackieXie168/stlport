#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define partsum0_test main
#endif
#endif
int partsum0_test(int, char**)
{
  cout<<"Results of partsum0_test:"<<endl;
int numbers[6] = { 1, 2, 3, 4, 5, 6 };

  int result[6];
  partial_sum((int*)numbers, (int*)numbers + 6, (int*)result);
  for(int i = 0; i < 6; i ++)
    cout << result[i] << ' ';
  cout << endl;
  return 0;
}
