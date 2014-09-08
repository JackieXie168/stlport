#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define eqlrnge0_test main
#endif
#endif
int eqlrnge0_test(int, char**)
{
  cout<<"Results of eqlrnge0_test:"<<endl;
int numbers[10] = { 0, 0, 1, 1, 2, 2, 2, 2, 3, 3 };

  pair <int*, int*> range = equal_range((int*)numbers, (int*)numbers + 10, 2);
  cout
    << "2 can be inserted from before index "
    <<(range.first - numbers)
    << " to before index "
    <<(range.second - numbers)
    << endl;
  return 0;
}
