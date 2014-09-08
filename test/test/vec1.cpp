#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>
#include <vector.h>

#ifdef MAIN 
#define vec1_test main
#endif
#endif
int vec1_test(int, char**)
{
  //   cout<<"Sizeof(vector) is "<<sizeof(vector<int>)<<endl;
  //  cout<<"Sizeof(fw) is "<<sizeof(forward_iterator_tag)<<endl;
  //  cout<<"Sizeof(ra) is "<<sizeof(random_access_iterator_tag)<<endl;
  cout<<"Results of vec1_test:"<<endl;
  vector<int> v1; // Empty vector of integers.
  cout << "empty = " << v1.empty() << endl;
  cout << "size = " << v1.size() << endl;
  cout << "max_size = " << v1.max_size() << endl;
  v1.push_back(42); // Add an integer to the vector.
  cout << "size = " << v1.size() << endl;
  cout << "v1[0] = " << v1[0] << endl;
  return 0;
}
