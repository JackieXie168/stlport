#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define maxelem1_test main
#endif
#endif
int maxelem1_test(int, char**)
{
  cout<<"Results of maxelem1_test:"<<endl;
int numbers[6] = { 4, 10, 56, 11, -42, 19 };

  cout << *max_element((int*)numbers, (int*)numbers + 6) << endl;
  return 0;
}
