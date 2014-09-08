#ifndef _rand_h
#define _rand_h
#include <stdlib.h>
class MyRandomGenerator
{
  public:
    unsigned long operator()(unsigned long n_);
};

unsigned long
MyRandomGenerator::operator()(unsigned long n_)
{
  return rand() % n_;
}
#endif // _rand_h
