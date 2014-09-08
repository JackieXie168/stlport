/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef __SGI_STL_INTERNAL_QUEUE_H
#define __SGI_STL_INTERNAL_QUEUE_H

__STL_BEGIN_NAMESPACE

#ifndef __STL_LIMITED_DEFAULT_TEMPLATES
template <class _Tp, class _Sequence = deque<_Tp> >
#else
template <class _Tp, class _Sequence>
#endif
class queue;

template <class _Tp, class _Seq>
inline bool operator==(const queue<_Tp, _Seq>&, const queue<_Tp, _Seq>&);

template <class _Tp, class _Seq>
inline bool operator<(const queue<_Tp, _Seq>&, const queue<_Tp, _Seq>&);

template <class _Tp, class _Sequence>
class queue {
friend inline bool __STD_QUAL operator== __STL_NULL_TMPL_ARGS 
(const queue<_Tp, _Sequence>&, const queue<_Tp, _Sequence>&);
friend inline bool __STD_QUAL operator< __STL_NULL_TMPL_ARGS 
(const queue<_Tp, _Sequence>&, const queue<_Tp, _Sequence>&);
public:
  typedef typename _Sequence::value_type      value_type;
  typedef typename _Sequence::size_type       size_type;
  typedef          _Sequence                  container_type;

  typedef typename _Sequence::reference       reference;
  typedef typename _Sequence::const_reference const_reference;
protected:
  _Sequence c;
public:
  queue() : c() {}
  explicit queue(const _Sequence& __c) : c(__c) {}

  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  reference front() { return c.front(); }
  const_reference front() const { return c.front(); }
  reference back() { return c.back(); }
  const_reference back() const { return c.back(); }
  void push(const value_type& __x) { c.push_back(__x); }
  void pop() { c.pop_front(); }
};

template <class _Tp, class _Sequence>
bool 
operator==(const queue<_Tp, _Sequence>& __x, const queue<_Tp, _Sequence>& __y)
{
  return __x.c == __y.c;
}

template <class _Tp, class _Sequence>
bool
operator<(const queue<_Tp, _Sequence>& __x, const queue<_Tp, _Sequence>& __y)
{
  return __x.c < __y.c;
}

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER

template <class _Tp, class _Sequence>
bool
operator!=(const queue<_Tp, _Sequence>& __x, const queue<_Tp, _Sequence>& __y)
{
  return !(__x == __y);
}

template <class _Tp, class _Sequence>
bool 
operator>(const queue<_Tp, _Sequence>& __x, const queue<_Tp, _Sequence>& __y)
{
  return __y < __x;
}

template <class _Tp, class _Sequence>
bool 
operator<=(const queue<_Tp, _Sequence>& __x, const queue<_Tp, _Sequence>& __y)
{
  return !(__y < __x);
}

template <class _Tp, class _Sequence>
bool 
operator>=(const queue<_Tp, _Sequence>& __x, const queue<_Tp, _Sequence>& __y)
{
  return !(__x < __y);
}

#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

#if defined ( __STL_DEFAULT_TEMPLATE_PARAM ) && !defined ( __STL_TEMPLATE_PARAM_SUBTYPE_BUG )
template <class _Tp, class _Sequence = vector<_Tp>, 
          class _Compare = less<typename _Sequence::value_type> >
#else
template <class _Tp, class _Sequence, class _Compare>
#endif
class  priority_queue {
public:
  typedef typename _Sequence::value_type      value_type;
  typedef typename _Sequence::size_type       size_type;
  typedef          _Sequence                  container_type;

  typedef typename _Sequence::reference       reference;
  typedef typename _Sequence::const_reference const_reference;
protected:
  _Sequence c;
  _Compare _comp;		//*TY 01/10/1999 - ugrified comp
public:
  priority_queue() : c() {}
  explicit priority_queue(const _Compare& __x) :  c(), _comp(__x) {}		//*TY 01/10/1999 - ugrified comp
  priority_queue(const _Compare& __x, const _Sequence& __s) 
    : c(__s), _comp(__x) 		//*TY 01/10/1999 - ugrified comp
    { make_heap(c.begin(), c.end(), _comp); }		//*TY 01/10/1999 - ugrified comp

#ifdef __STL_MEMBER_TEMPLATES
  template <class _InputIterator>
  priority_queue(_InputIterator __first, _InputIterator __last) 
    : c(__first, __last) { make_heap(c.begin(), c.end(), _comp); }		//*TY 01/10/1999 - ugrified comp

  template <class _InputIterator>
  priority_queue(_InputIterator __first, 
                 _InputIterator __last, const _Compare& __x)
    : c(__first, __last), _comp(__x) 		//*TY 01/10/1999 - ugrified comp
    { make_heap(c.begin(), c.end(), _comp); }		//*TY 01/10/1999 - ugrified comp

  template <class _InputIterator>
  priority_queue(_InputIterator __first, _InputIterator __last,
                 const _Compare& __x, const _Sequence& __s)
  : c(__s), _comp(__x)		//*TY 01/10/1999 - ugrified comp
  { 
    c.insert(c.end(), __first, __last);
    make_heap(c.begin(), c.end(), _comp);		//*TY 01/10/1999 - ugrified comp
  }

#else /* __STL_MEMBER_TEMPLATES */
  priority_queue(const value_type* __first, const value_type* __last) 
    : c(__first, __last) { make_heap(c.begin(), c.end(), _comp); }		//*TY 01/10/1999 - ugrified comp

  priority_queue(const value_type* __first, const value_type* __last, 
                 const _Compare& __x) 
    : c(__first, __last), _comp(__x)		//*TY 01/10/1999 - ugrified comp
    { make_heap(c.begin(), c.end(), _comp); }		//*TY 01/10/1999 - ugrified comp

  priority_queue(const value_type* __first, const value_type* __last, 
                 const _Compare& __x, const _Sequence& __c)
    : c(__c), _comp(__x) 		//*TY 01/10/1999 - ugrified comp
  { 
    c.insert(c.end(), __first, __last);
    make_heap(c.begin(), c.end(), _comp);		//*TY 01/10/1999 - ugrified comp
  }
#endif /* __STL_MEMBER_TEMPLATES */

  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  const_reference top() const { return c.front(); }
  void push(const value_type& __x) {
    __STL_TRY {
      c.push_back(__x); 
      push_heap(c.begin(), c.end(), _comp);		//*TY 01/10/1999 - ugrified comp
    }
    __STL_UNWIND(c.clear());
  }
  void pop() {
    __STL_TRY {
      pop_heap(c.begin(), c.end(), _comp);		//*TY 01/10/1999 - ugrified comp
      c.pop_back();
    }
    __STL_UNWIND(c.clear());
  }
};

#if defined  (__STL_DEFAULT_TEMPLATE_PARAM)
#  define simple_queue queue
#  define simple_priority_queue priority_queue
# else

// provide a "default" queue adaptor
template <class _Tp>
class simple_queue : public queue<_Tp, deque<_Tp> > 
{
public:
    simple_queue() {}
    ~simple_queue() {}
};

// provide a "simple" priority queue adaptor
template <class _Tp>
class simple_priority_queue : public priority_queue<_Tp, deque<_Tp> , less<_Tp> > 
{
    typedef priority_queue<_Tp, deque<_Tp> , less<_Tp> > _Super;
public:
    typedef typename _Super::value_type value_type;
    typedef typename _Super::size_type size_type;
    simple_priority_queue() : priority_queue() {}
    simple_priority_queue(const value_type* __first, const value_type* __last) : 
         priority_queue(__first,__last){}
};

#endif /* __STL_DEFAULT_TEMPLATE_PARAM */

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_QUEUE_H */

// Local Variables:
// mode:C++
// End:
