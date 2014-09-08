#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <pair.h>
#include <iostream.h>

#ifdef MAIN 
#define pair1_test main
#endif
#endif
int pair1_test(int, char**)
{
  cout<<"Results of pair1_test:"<<endl;
  pair<int, int> p = make_pair(1, 10);
  cout << "p.first = " << p.first << ", p.second = " << p.second << endl;
  return 0;
}
