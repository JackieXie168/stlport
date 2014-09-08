#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>

#ifdef MAIN 
#define alg1_test main
#endif
#endif
int alg1_test(int, char**)
{
  cout<<"Results of alg1_test:"<<endl;
  int i = __STLPORT_STD::min(4, 7);
  cout << "min(4, 7) = " << i << endl;
  char c = __STLPORT_STD::max('a', 'z');
  cout << "max('a', 'z') = " << c << endl;
  return 0;
}
