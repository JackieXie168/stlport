#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>
#include <string.h>

#ifdef MAIN 
#define eqlrnge2_test main
#endif
#endif
int eqlrnge2_test(int, char**)
{
  cout<<"Results of eqlrnge2_test:"<<endl;
char chars[] = "aabbccddggghhklllmqqqqssyyzz";

  const unsigned count = sizeof(chars) - 1;
  ostream_iterator<char> iter(cout);
  cout << "Within the collection:\n\t";
  copy(chars, chars + count, iter);
  pair <char*, char*> range =
	 equal_range((char*)chars, (char*)chars + count, 'q', less<char>());
  cout
    << "\nq can be inserted from before index "
    <<(range.first - chars)
    << " to before index "
    <<(range.second - chars)
    << endl;
  return 0;
}
