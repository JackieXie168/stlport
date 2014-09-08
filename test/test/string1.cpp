#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <string>
#include <iostream.h>

#ifdef MAIN 
#define string1_test main
#endif
#endif
int string1_test(int, char**)
{
  cout<<"Results of string1_test:"<<endl;
  char* array = "Hello, World!";
  STLPORT::string v(array);
  int i;
  cout << v << endl;
  v.erase(v.begin() + 1, v.end() - 1); // Erase all but first and last.
  for(i = 0; i < v.size(); i++)
    cout << "v[" << i << "] = " << v[i] << endl;
  cout << endl;
  v.insert(1, (char*)array);
  v.erase(v.begin()); // Erase first element.
  v.erase(v.end() - 1); // Erase last element.
  cout << v << endl;
  v.clear(); // Erase all.
  return 0;
}
