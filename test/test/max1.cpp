#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define max1_test main
#endif
#endif
int max1_test(int, char**)
{
  cout<<"Results of max1_test:"<<endl;
  cout << __STD::max(42, 100) << endl;
  return 0;
}
