#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>
#include <string.h>

#ifdef MAIN 
#define trnsfrm2_test main
#endif
static char map_char(char a_, int b_)
{
  return char(a_ + b_);
}
#endif
int trnsfrm2_test(int, char**)
{
  cout<<"Results of trnsfrm2_test:"<<endl;

#if defined (__MVS__)
int trans[] = {-11, 4, -6, -6, -18, 0, 18, -14, 6, 0, -1, -59};
#else
int trans[] = {-4, 4, -6, -6, -10, 0, 10, -6, 6, 0, -1, -77};
#endif
  char n[] = "Larry Mullen";
  const unsigned count = ::strlen(n);
  ostream_iterator <char> iter(cout);
  transform(n, n + count, trans, iter, map_char);
  cout << endl;
  return 0;
}
