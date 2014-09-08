#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define sort2_test main
#endif
#endif
int sort2_test(int, char**)
{
  cout<<"Results of sort2_test:"<<endl;
int array[] = { 1, 50, -10, 11, 42, 19 };

  int count = sizeof(array) / sizeof(array[0]);
  ostream_iterator <int> iter(cout, " ");
  cout << "before: ";
  copy(array, array + count, iter);
  cout << "\nafter: ";
  sort(array, array + count, greater<int>());
  copy(array, array + count, iter);
  cout << endl;
  return 0;
}
