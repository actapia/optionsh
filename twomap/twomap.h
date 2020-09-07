#ifndef TWOMAP_H
#define TWOMAP_H

#include <map>
#include <unordered_map>
#include "different_concept.h"
#include "map_defs.h"
#include "twomap_setter.h"

/* twomap is a class representing a map and its "inverse" multimap.
   The class implements a subset of methods common to unordered_map and unordered_multimap, on which
   the class is based.

   Although it should provide similar functionality to STL container types, it does not meet these
   standards.
*/

/* Unfortunately, due to limitations of C++, this class cannot be used with two identical types or
   two types that are convertible. The first may be obvious (How can we tell if a key is for the
   forward or inverse map?), but the second is less obvious. Shortly, it is a consequence of implicit
   conversion; there is ambiguity in which functions are to be called if the two types are
   convertible.
*/

template <typename S, typename T, typename CompareS = std::less<S>, typename CompareT = std::less<T>>
#ifdef __cpp_concepts
requires different<S,T>
#endif
class twomap {
public:
  // constructor
  twomap();
  // constructor (2)
  template <class input_it>
  twomap(input_it first, input_it last);
  // constructor (3)
  twomap(const twomap<S,T,CompareS,CompareT>& other);
  // constructor (4)
  twomap(twomap<S,T,CompareS,CompareT>&& other);
  // constructor (5)
  explicit twomap(std::initializer_list<std::pair<S,T>> init);
  explicit twomap(std::initializer_list<std::pair<T,S>> init);
  // = (1)
  twomap<S,T,CompareS,CompareT>& operator=(const twomap<S,T,CompareS,CompareT>& other);
  // = (2)
  twomap<S,T,CompareS,CompareT>& operator=(twomap<S,T,CompareS,CompareT>&& other);
  // = (3)
  twomap<S,T,CompareS,CompareT>& operator=(std::initializer_list<std::pair<S,T>> init);
  twomap<S,T,CompareS,CompareT>& operator=(std::initializer_list<std::pair<T,S>> init);
  // iterators
  typename forward_map<S,T,CompareS>::iterator S_begin();
  typename inverse_map<T,S,CompareT>::iterator T_begin();
  typename forward_map<S,T,CompareS>::const_iterator S_cbegin();
  typename inverse_map<T,S,CompareT>::const_iterator T_cbegin();
  typename forward_map<S,T,CompareS>::iterator S_end();
  typename inverse_map<T,S,CompareT>::iterator T_end();
  typename forward_map<S,T,CompareS>::const_iterator S_cend();
  typename inverse_map<T,S,CompareT>::const_iterator T_cend();
  // capacity
  bool empty();
  size_t size();
  size_t max_size();
  // clear
  void clear();
  // insert (1)
  typename std::pair<std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator>,bool> insert(const std::pair<S,T>& value);
  //typename std::pair<std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator>,bool> insert(std::pair<S,T>&& value);
  typename std::pair<std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator>,bool> insert(const std::pair<T,S>& value);
  // // insert (2)
  // template <class P>
  // typename std::pair<std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator>,bool> insert(P&& value);
  // emplace
  typename std::pair<std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator>,bool> emplace(S&& key, T&& value);
  typename std::pair<std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator>,bool> emplace(T&& value, S&& key);
  // erase (1)
  std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator> erase(typename forward_map<S,T,CompareS>::const_iterator pos);
  std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator> erase(typename inverse_map<T,S,CompareT>::const_iterator pos);
  // erase (2)
  std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator> erase(typename forward_map<S,T,CompareS>::const_iterator first, typename forward_map<S,T,CompareS>::const_iterator last);
  std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator> erase(typename inverse_map<T,S,CompareT>::const_iterator first, typename inverse_map<T,S,CompareT>::const_iterator last);
  // erase (3)
  size_t erase(const S& key);
  size_t erase(const T& key);
  // swap
  void swap(twomap<S,T,CompareS,CompareT>& other);
  // at
  twomap_setter<S,T,CompareS,CompareT> at(const S& key);
  const twomap_setter<S,T,CompareS,CompareT> at(const S& key) const;
  // []
  twomap_setter<S,T,CompareS,CompareT> operator[](const S& key);
  twomap_setter<S,T,CompareS,CompareT> operator[](S&& key);
  // count
  size_t count(const T& key) const;
  size_t count(const S& key) const;
  // additional counts
  template <typename K>
  size_t S_count(const K& key) const;
  template <typename K>
  size_t T_count(const K& key) const;  
  // find (1)
  typename forward_map<S,T,CompareS>::iterator find(const S& key);
  typename inverse_map<T,S,CompareT>::iterator find(const T& key);
  // find (2)
  typename forward_map<S,T,CompareS>::const_iterator find(const S& key) const;
  typename inverse_map<T,S,CompareT>::const_iterator find(const T& key) const;
  // additional finds
  template <typename K>
  typename forward_map<S,T,CompareS>::iterator S_find(const K& key);
  template <typename K>
  typename inverse_map<T,S,CompareT>::iterator T_find(const K& key);
  template <typename K>
  typename forward_map<S,T,CompareS>::iterator S_find(const K& key) const;
  template <typename K>
  typename inverse_map<T,S,CompareT>::iterator T_find(const K& key) const;
  // contains
  bool contains(const S& key) const;
  bool contains(const T& key) const;
  // additional contains
  template <typename K>
  bool S_contains(const K& key) const;
  template <typename K>
  bool T_contains(const K& key) const;
  // equal_range (1)
  typename std::pair<typename forward_map<S,T,CompareS>::iterator,typename forward_map<S,T,CompareS>::iterator> equal_range(const S& key);
  typename std::pair<typename inverse_map<T,S,CompareT>::iterator,typename inverse_map<T,S,CompareT>::iterator> equal_range(const T& key);
  // equal_range (2)
  typename std::pair<typename forward_map<S,T,CompareS>::const_iterator,typename forward_map<S,T,CompareS>::const_iterator> equal_range(const S& key) const;
  typename std::pair<typename inverse_map<T,S,CompareT>::const_iterator,typename inverse_map<T,S,CompareT>::const_iterator> equal_range(const T& key) const;
  // additional equal_ranges
  template <typename K>
  typename std::pair<typename forward_map<S,T,CompareS>::iterator,typename forward_map<S,T,CompareS>::iterator> S_equal_range(const K& key);
  template <typename K>
  typename std::pair<typename inverse_map<T,S,CompareT>::const_iterator,typename inverse_map<T,S,CompareT>::const_iterator> T_equal_range(const K& key);
  template <typename K>
  typename std::pair<typename forward_map<S,T,CompareS>::iterator,typename forward_map<S,T,CompareS>::iterator> S_equal_range(const K& key) const;
  template <typename K>
  typename std::pair<typename inverse_map<T,S,CompareT>::const_iterator,typename inverse_map<T,S,CompareT>::const_iterator> T_equal_range(const K& key) const;
  // comparison
  template <typename U, typename V,typename CompareU,typename CompareV>
  friend bool operator==(const twomap<U,V,CompareU,CompareV>& lhs, const twomap<U,V,CompareU,CompareV>& rhs);
  template <typename U, typename V,typename CompareU,typename CompareV>
  friend bool operator!=(const twomap<U,V,CompareU,CompareV>& lhs, const twomap<U,V,CompareU,CompareV>& rhs);  
private:
  // map is the forward map.
  forward_map<S,T,CompareS> map;
  // inverse in the inverse multimap.
  inverse_map<T,S,CompareT> inverse;
};

#include "twomap.cpp"

#endif
