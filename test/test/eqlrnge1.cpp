#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define eqlrnge1_test main
#endif
#endif
int eqlrnge1_test(int, char**)
{
  cout<<"Results of eqlrnge1_test:"<<endl;
  typedef vector <int> IntVec;
  IntVec v(10);
  for(int i = 0; i < v.size(); i++)
    v[i] = i / 3;
  ostream_iterator<int> iter(cout, " ");
  cout << "Within the collection:\n\t";
  copy(v.begin(), v.end(), iter);
  pair <IntVec::iterator, IntVec::iterator> range =
	equal_range(v.begin(), v.end(), 2);
  cout
    << "\n2 can be inserted from before index "
    <<(range.first - v.begin())
    << " to before index "
    <<(range.second - v.begin())
    << endl;
  return 0;
}
