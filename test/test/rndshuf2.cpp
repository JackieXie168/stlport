#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <vector.h>
#include <iostream.h>
#include "rand.h"

#ifdef MAIN 
#define rndshuf2_test main
#endif
#endif

int rndshuf2_test(int, char**)
{
  cout<<"Results of rndshuf2_test:"<<endl;

  vector <int> v1(10);
  iota(v1.begin(), v1.end(), 0);
  ostream_iterator <int> iter(cout, " ");
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  MyRandomGenerator r;
  for(int i = 0; i < 3; i++)
  {
    random_shuffle(v1.begin(), v1.end(), r);
    copy(v1.begin(), v1.end(), iter);
    cout << endl;
  }
  return 0;
}
