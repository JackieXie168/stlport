#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <multimap.h>
#include <iostream.h>

#ifdef MAIN 
#define mmap1_test main
#endif
#endif
int mmap1_test(int, char**)
{
  cout<<"Results of mmap1_test:"<<endl;
  typedef multimap<char, int, less<char> > mmap;
  mmap m;
  cout << "count('X') = " << m.count('X') << endl;
  m.insert(pair<const char, int>('X', 10)); // Standard way.
  cout << "count('X') = " << m.count('X') << endl;
//  m.insert('X', 20); // Non-standard, but very convenient!
  m.insert(pair<const char, int>('X', 20));	// jbuck: standard way
  cout << "count('X') = " << m.count('X') << endl;
//  m.insert('Y', 32);
  m.insert(pair<const char, int>('Y', 32));	// jbuck: standard way
  mmap::iterator i = m.find('X'); // Find first match.
  while(i != m.end()) // Loop until end is reached.
  {
    cout <<(*i).first << " -> " <<(*i).second << endl;
    i++;
  }
  int count = m.erase('X');
  cout << "Erased " << count << " items" << endl;
  return 0;
}
