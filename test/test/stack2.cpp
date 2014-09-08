#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>
#include <stack.h>
#include <list.h>

#ifdef MAIN 
#define stack2_test main
#endif
#endif
int stack2_test(int, char**)
{
  cout<<"Results of stack2_test:"<<endl;
  stack<int, list<int> > s;
  s.push(42);
  s.push(101);
  s.push(69);
  while(!s.empty())
  {
    cout << s.top() << endl;
    s.pop();
  }
  return 0;
}
