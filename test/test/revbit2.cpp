#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>
#include <list.h>

#ifdef MAIN 
#define revbit2_test main
#endif
#endif
int revbit2_test(int, char**)
{
  cout<<"Results of revbit2_test:"<<endl;
int array [] = { 1, 5, 2, 3 };

  list<int> v(array, array + 4);
  STLPORT::list<int>::reverse_iterator r;
  for(r = v.rbegin(); !(r == v.rend()); r++)
    cout << *r << endl;
  return 0;
}
