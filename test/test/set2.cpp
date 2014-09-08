#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>
#include <set.h>

#ifdef MAIN 
#define set2_test main
#endif
#endif
int set2_test(int, char**)
{
  cout<<"Results of set2_test:"<<endl;
  set<int, less<int> > s;
  pair<__STD::set<int, less<int> >::const_iterator, bool> p = s.insert(42);
  if(p.second)
   cout << "Inserted new element " << *(p.first) << endl;
  else
   cout << "Existing element = " << *(p.first) << endl;
  p = s.insert(42);
  if(p.second)
   cout << "Inserted new element " << *(p.first) << endl;
  else
   cout << "Existing element = " << *(p.first) << endl;
  return 0;
}
