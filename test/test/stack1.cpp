#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>
#include <stack.h>
#include <deque.h>

#ifdef MAIN 
#define stack1_test main
#endif
#endif
int stack1_test(int, char**)
{
  cout<<"Results of stack1_test:"<<endl;
  stack<int, deque<int> > s;
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
