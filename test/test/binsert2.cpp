#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <vector.h>
#include <algo.h>

#ifdef MAIN 
#define binsert2_test main
#endif
#endif
int binsert2_test(int, char**)
{
  cout<<"Results of binsert2_test:"<<endl;
char* array [] = { "laurie", "jennifer", "leisa" };

  vector<char*> names;
  copy(array, array + 3, back_inserter(names));
  __STLPORT_STD::vector<char*>::iterator i;
  for(i = names.begin(); i != names.end(); i++)
    cout << *i << endl;
  return 0;
}
