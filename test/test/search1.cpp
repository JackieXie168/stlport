#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <vector.h>
#include <iostream.h>

#ifdef MAIN 
#define search1_test main
#endif
#endif
int search1_test(int, char**)
{
  cout<<"Results of search1_test:"<<endl;
  typedef vector <int> IntVec;
  IntVec v1(10);
  iota(v1.begin(), v1.end(), 0);
  IntVec v2(3);
  iota(v2.begin(), v2.end(), 50);
  ostream_iterator <int> iter(cout, " ");

  cout << "v1: ";
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  cout << "v2: ";
  copy(v2.begin(), v2.end(), iter);
  cout << endl;

  IntVec::iterator location;
  location = search(v1.begin(), v1.end(), v2.begin(), v2.end());

  if(location == v1.end())
    cout << "v2 not contained in v1" << endl;
  else
    cout << "Found v2 in v1 at offset: " << location - v1.begin() << endl;

  iota(v2.begin(), v2.end(), 4);
  cout << "v1: ";
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  cout << "v2: ";
  copy(v2.begin(), v2.end(), iter);
  cout << endl;

  location = search(v1.begin(), v1.end(), v2.begin(), v2.end());

  if(location == v1.end())
    cout << "v2 not contained in v1" << endl;
  else
    cout << "Found v2 in v1 at offset: " << location - v1.begin() << endl;

  return 0;
}
