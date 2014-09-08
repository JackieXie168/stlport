#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define ostmit_test main
#endif
#endif
int ostmit_test(int, char**)
{
  cout<<"Results of ostmit_test:"<<endl;
int array [] = { 1, 5, 2, 4 };

  char* string = "hello";
  ostream_iterator<char> it1(cout);
  copy(string, string + 5, it1);
  cout << endl;
  ostream_iterator<int> it2(cout);
  copy(array, array + 4, it2);
  cout << endl;
  return 0;
}
