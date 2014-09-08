#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <list.h>

#ifdef MAIN 
#define list1_test main
#endif
#endif
int list1_test(int, char**)
{
  cout<<"Results of list1_test:"<<endl;
int array1 [] = { 9, 16, 36 };
int array2 [] = { 1, 4 };

  list<int> l1(array1, array1 + 3);
  list<int> l2(array2, array2 + 2);
  __STD::list<int>::iterator i1 = l1.begin();
  l1.splice(i1, l2);
  __STD::list<int>::iterator i2 = l1.begin();
  while(i2 != l1.end())
    cout << *i2++ << endl;
  return 0;
}
