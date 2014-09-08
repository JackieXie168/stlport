#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>
#include <string.h>

#ifdef MAIN 
#define unique2_test main
#endif
static bool str_equal(const char* a_, const char* b_)
{
  return ::strcmp(a_, b_) == 0 ? 1 : 0;
}
#endif
int unique2_test(int, char**)
{
  cout<<"Results of unique2_test:"<<endl;

char* labels[] = { "Q","Q","W","W","E","E","R","T","T","Y","Y" };

  const unsigned count = sizeof(labels) / sizeof(labels[0]);
  ostream_iterator <char*> iter(cout);
  copy((char**)labels, (char**)labels + count, iter);
  cout << endl;
  unique((char**)labels, (char**)labels + count, str_equal);
  copy((char**)labels, (char**)labels + count, iter);
  cout << endl;
  return 0;
}
