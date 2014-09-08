#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <deque.h>
#include <algo.h>

#ifdef MAIN 
#define finsert2_test main
#endif
#endif
int finsert2_test(int, char**)
{
  cout<<"Results of finsert2_test:"<<endl;
char* array [] = { "laurie", "jennifer", "leisa" };

  deque<char*> names;
  copy(array, array + 3, front_inserter(names));
  __STD::deque<char*>::iterator i;
  for(i = names.begin(); i != names.end(); i++)
    cout << *i << endl;
  return 0;
}
