#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>
#include <stack.h>
#include <list.h>

#ifdef MAIN 
#define queue1_test main
#endif
#endif
int queue1_test(int, char**)
{
  cout<<"Results of queue1_test:"<<endl;
  queue<int, list<int> > q;
  q.push(42);
  q.push(101);
  q.push(69);
  while(!q.empty())
  {
    cout << q.front() << endl;
    q.pop();
  }
  return 0;
}
