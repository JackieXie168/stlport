#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>
#include <string.h>

#ifdef MAIN 
#define inrprod1_test main
#endif
#endif
int inrprod1_test(int, char**)
{
  cout<<"Results of inrprod1_test:"<<endl;
  vector <int> v1(3);
  vector <int> v2(v1.size());
  for(int i = 0; i < v1.size(); i++)
  {
    v1[i] = i + 1;
    v2[i] = v1.size() - i;
  }
  ostream_iterator<int> iter(cout, " ");
  cout << "Inner product(sum of products) of:\n\t";
  copy(v1.begin(), v1.end(), iter);
  cout << "\n\t";
  copy(v2.begin(), v2.end(), iter);
  int result = inner_product(v1.begin(), v1.end(), v2.begin(), 0);
  cout << "\nis: " << result << endl;
  return 0;
}
