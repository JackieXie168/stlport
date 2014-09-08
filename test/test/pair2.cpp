#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <pair.h>
#include <iostream.h>

#ifdef MAIN 
#define pair2_test main
#endif
#endif
int pair2_test(int, char**)
{
  cout<<"Results of pair2_test:"<<endl;
  pair<int, int> p = make_pair(1, 10);
  cout << "p.first = " << p.first << endl;
  cout << "p.second = " << p.second << endl;
  return 0;
}
