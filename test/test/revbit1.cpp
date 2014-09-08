#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>
#include <list.h>

#ifdef MAIN 
#define revbit1_test main
#endif
#endif
int revbit1_test(int, char**)
{
  cout<<"Results of revbit1_test:"<<endl;
int array [] = { 1, 5, 2, 3 };

  list<int> v(array, array + 4);
  __STD::list<int>::reverse_iterator r(v.rbegin());
  while(!(r == v.rend()))
    cout << *r++ << endl;
  return 0;
}
