#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <vector.h>
#include <algo.h>

#ifdef MAIN 
#define vec7_test main
#endif
#endif
int vec7_test(int, char**)
{
  cout<<"Results of vec7_test:"<<endl;
int array1 [] = { 1, 4, 25 };
int array2 [] = { 9, 16 };

  vector<int> v(array1, array1 + 3);
  v.insert(v.begin(), 0); // Insert before first element.
  v.insert(v.end(), 36); // Insert after last element.
  int i;
  for(i = 0; i < v.size(); i++)
    cout << "v[" << i << "] = " << v[i] << endl;
  cout << endl;
  // Insert contents of array2 before fourth element.
  v.insert(v.begin() + 3, array2, array2 + 2);
  for(i = 0; i < v.size(); i++)
    cout << "v[" << i << "] = " << v[i] << endl;
  cout << endl;
  return 0;
}
