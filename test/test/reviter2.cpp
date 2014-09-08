#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <vector.h>
#include <algo.h>

#ifdef MAIN 
#define reviter2_test main
#endif
#endif
int reviter2_test(int, char**)
{
  cout<<"Results of reviter2_test:"<<endl;
int array [] = { 1, 5, 2, 3 };

  STLPORT::vector<int> v(array, array + 4);
  STLPORT::vector<int>::reverse_iterator r;
  for(r = v.rbegin(); r != v.rend(); r++)
    cout << *r << endl;
  return 0;
}
