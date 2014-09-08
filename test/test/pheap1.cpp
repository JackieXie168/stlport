#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <vector.h>
#include <iostream.h>

#ifdef MAIN 
#define pheap1_test main
#endif
#endif
int pheap1_test(int, char**)
{
  cout<<"Results of pheap1_test:"<<endl;
  vector<int> v;

  v.push_back(1);
  v.push_back(20);
  v.push_back(4);
  make_heap(v.begin(), v.end());

  v.push_back(7);
  push_heap(v.begin(), v.end());

  sort_heap(v.begin(), v.end());
  ostream_iterator<int> iter(cout, " ");
  copy(v.begin(), v.end(), iter);
  cout << endl;

  return 0;
}
