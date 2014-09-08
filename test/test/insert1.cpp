#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <deque.h>
#include <algo.h>

#ifdef MAIN 
#define insert1_test main
#endif
#endif
int insert1_test(int, char**)
{
  cout<<"Results of insert1_test:"<<endl;
char* array1 [] = { "laurie", "jennifer", "leisa" };
char* array2 [] = { "amanda", "saskia", "carrie" };

  deque<char*> names(array1, array1 + 3);
  __STLPORT_STD::deque<char*>::iterator i = names.begin() + 2;
  copy(array2, array2 + 3, insert_iterator<deque <char*> >(names, i));
  __STLPORT_STD::deque<char*>::iterator j;
  for(j = names.begin(); j != names.end(); j++)
    cout << *j << endl;
  return 0;
}
