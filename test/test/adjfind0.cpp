#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define adjfind0_test main
#endif
#endif
int adjfind0_test(int, char**)
{
  cout<<"Results of adjfind0_test:"<<endl;
int numbers1 [5] = { 1, 2, 4, 8, 16 };
int numbers2 [5] = { 5, 3, 2, 1, 1 };

  int* location = adjacent_find((int*)numbers1, (int*)numbers1 + 5);

  if(location != numbers1 + 5)
    cout
      << "Found adjacent pair of: "
      << *location
      << " at offset "
      <<(location - numbers1)
      << endl;
  else
    cout << "No adjacent pairs" << endl;
  location = adjacent_find((int*)numbers2, (int*)numbers2 + 5);
  if(location != numbers2 + 5)
    cout
      << "Found adjacent pair of: "
      << *location
      << " at offset "
      <<(location - numbers2)
      << endl;
  else
    cout << "No adjacent pairs" << endl;
  return 0;
}
