#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define min1_test main
#endif
#endif
int min1_test(int, char**)
{
  cout<<"Results of min1_test:"<<endl;
  cout << STLPORT::min(42, 100) << endl;
  return 0;
}
