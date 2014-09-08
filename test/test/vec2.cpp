#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <vector.h>
#include <algo.h>

#ifdef MAIN 
#define vec2_test main
#endif
static void print(vector<double>& vector_)
{
  for(int i = 0; i < vector_.size(); i++)
    cout << vector_[i] << " ";
  cout << endl;
}
#endif
int vec2_test(int, char**)
{
  cout<<"Results of vec2_test:"<<endl;

  vector<double> v1; // Empty vector of doubles.
  v1.push_back(32.1);
  v1.push_back(40.5);
  vector<double> v2; // Another empty vector of doubles.
  v2.push_back(3.56);
  cout << "v1 = ";
  print(v1);
  cout << "v2 = ";
  print(v2);
  v1.swap(v2); // Swap the vector's contents.
  cout << "v1 = ";
  print(v1);
  cout << "v2 = ";
  print(v2);
  v2 = v1; // Assign one vector to another.
  cout << "v2 = ";
  print(v2);
  return 0;
}
