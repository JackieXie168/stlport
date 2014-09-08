#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <vector.h>
#include <algo.h>

#ifdef MAIN 
#define binsert1_test main
#endif
#endif
int binsert1_test(int, char**)
{
  cout<<"Results of binsert1_test:"<<endl;
char* array [] = { "laurie", "jennifer", "leisa" };

  vector<char*> names;
  copy(array, array + 3, back_insert_iterator<vector <char*> >(names));
  __STLPORT_STD::vector<char*>::iterator i;
  for(i = names.begin(); i != names.end(); i++)
    cout << *i << endl;
  return 0;
}
