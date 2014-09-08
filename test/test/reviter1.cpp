#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <vector.h>
#include <algo.h>

#ifdef MAIN 
#define reviter1_test main
#endif
#endif
int reviter1_test(int, char**)
{
  cout<<"Results of reviter1_test:"<<endl;
int array [] = { 1, 5, 2, 3 };

  vector<int> v(array, array + 4);
//  typedef reverse_iterator<typename vector<int>::iterator, int, 
//    typename vector<int>::reference, typename vector<int>::difference_type> reviter;
  typedef STLPORT::vector<int>::reverse_iterator reviter;
  reviter r(v.end());
  while(!(r ==v.rbegin()))
    cout << *r++ << endl;
  return 0;
}
