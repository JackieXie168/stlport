#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <list.h>

#ifdef MAIN 
#define list4_test main
#endif
#endif
int list4_test(int, char**)
{
  cout<<"Results of list4_test:"<<endl;
int array1 [] = { 1, 3, 6, 7 };
int array2 [] = { 2, 4 };

  list<int> l1(array1, array1 + 4);
  list<int> l2(array2, array2 + 2);
  l1.merge(l2);
  for(__STD::list<int>::iterator i = l1.begin(); i != l1.end(); i++)
    cout << *i;
  cout << endl;
  return 0;
}
