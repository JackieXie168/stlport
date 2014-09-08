#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <list.h>

#ifdef MAIN 
#define list3_test main
#endif
#endif
int list3_test(int, char**)
{
  cout<<"Results of list3_test:"<<endl;
char array [] = { 'x', 'l', 'x', 't', 's', 's' };

  list<char> str(array, array + 6);
  __STD::list<char>::iterator i;
  cout << "original: ";
  for(i = str.begin(); i != str.end(); i++)
    cout << *i;
  cout << endl;
  cout << "reversed: ";
  str.reverse();
  for(i = str.begin(); i != str.end(); i++)
    cout << *i;
  cout << endl;
  cout << "removed: ";
  str.remove('x');
  for(i = str.begin(); i != str.end(); i++)
    cout << *i;
  cout << endl;
  cout << "uniqued: ";
  str.unique();
  for(i = str.begin(); i != str.end(); i++)
    cout << *i;
  cout << endl;
  cout << "sorted: ";
  str.sort();
  for(i = str.begin(); i != str.end(); i++)
    cout << *i;
  cout << endl;
  return 0;
}
