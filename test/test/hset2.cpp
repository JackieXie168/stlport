#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>
#include <hash_set.h>

#ifdef MAIN 
#define hset2_test main
#endif
#endif
int hset2_test(int, char**)
{
  cout<<"Results of hset2_test:"<<endl;
  hash_set<int, hash<int>, equal_to<int> > s;
  pair<__STD::hash_set<int, hash<int>, equal_to<int> >::const_iterator, bool> p = s.insert(42);
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
