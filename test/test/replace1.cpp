#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <vector.h>
#include <iostream.h>

#ifdef MAIN 
#define replace1_test main
#endif
#endif
int replace1_test(int, char**)
{
  cout<<"Results of replace1_test:"<<endl;
  vector <int> v1(10);
  for(int i = 0; i < v1.size(); i++)
    v1[i] = i % 5;
  ostream_iterator <int> iter(cout, " ");
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  replace(v1.begin(), v1.end(), 2, 42);
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  return 0;
}
