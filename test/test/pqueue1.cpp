#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>
#include <deque.h>
#include <stack.h>

#ifdef MAIN 
#define pqueue1_test main
#endif
#endif
int pqueue1_test(int, char**)
{
  cout<<"Results of pqueue1_test:"<<endl;
  priority_queue<int, deque<int>, less<int> > q;
  q.push(42);
  q.push(101);
  q.push(69);
  while(!q.empty())
  {
    cout << q.top() << endl;
    q.pop();
  }
  return 0;
}
