#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <vector.h>
#include <algo.h>

#ifdef MAIN 
#define iter2_test main
#endif
#endif
static void print(const vector<const char*>& v_)
{
	__STD::vector<const char*>::const_iterator i;
  for(i = v_.begin(); i != v_.end(); i++)
    cout << *i << endl;
}
int iter2_test(int, char**)
{
  cout<<"Results of iter2_test:"<<endl;
  vector<const char*> v;
  v.push_back((char*) "zippy");
  v.push_back((char*) "motorboy");
  print(v);
  return 0;
}
