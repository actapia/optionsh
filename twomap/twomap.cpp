#include <algorithm>
#include <assert.h>
#include <cstring>
#include <iterator>
#include <stdexcept>
#include <unordered_map>
#include <iostream>
#include "twomap.h"
#include "twomap_setter.h"
#include "map_defs.h"

//static_assert(strcmp(__FILE__,"twomap.cpp") != 0,"Do not compile this file.");

template <typename S, typename T, typename CompareS, typename CompareT>
twomap<S,T,CompareS,CompareT>::twomap() {
  
}

template <typename S, typename T, typename CompareS, typename CompareT>
template <class input_it>
twomap<S,T,CompareS,CompareT>::twomap(input_it first, input_it last) {
  // This constructor creates a twomap from the range defined by the iterators first and last.
  for (auto it = first; it != last; ++it) {
    (*this)[it->first] = it->second;
  }
}

template <typename S, typename T, typename CompareS, typename CompareT>
twomap<S,T,CompareS,CompareT>::twomap(const twomap<S,T,CompareS,CompareT>& other) {
  // Copy constructor
  map = other.map;
  inverse = other.inverse;
}

template <typename S, typename T, typename CompareS, typename CompareT>
twomap<S,T,CompareS,CompareT>::twomap(twomap<S,T,CompareS,CompareT>&& other) {
  // Move constructor
  map = other.map;
  other.map = nullptr;
  inverse = other.inverse;
  other.inverse = nullptr;
}

template <typename S, typename T, typename CompareS, typename CompareT>
twomap<S,T,CompareS,CompareT>::twomap(std::initializer_list<std::pair<S,T>> init) {
  // This constructor creates a twomap with the contents of the initializer list init.
  // Note: for this constructor, the list is a list of std::pair<S,T>.
  for (auto it = init.begin(); it != init.end(); ++it) {
    (*this)[it->first] = it->second;
  }
}

template <typename S, typename T, typename CompareS, typename CompareT>
twomap<S,T,CompareS,CompareT>::twomap(std::initializer_list<std::pair<T,S>> init) {
  // This constructor creates a twomap with the contents of the initializer list init.
  // Note: for this constructor, the list is a list of std::pair<T,S>.
  for (auto it = init.begin(); it != init.end(); ++it) {
    (*this)[it->second] = it->first;
  }
}

template <typename S, typename T, typename CompareS, typename CompareT>
twomap<S,T,CompareS,CompareT>& twomap<S,T,CompareS,CompareT>::operator=(const twomap<S,T,CompareS,CompareT>& other) {
  // Copy assignment operator.
  return twomap(other);
}

template <typename S, typename T, typename CompareS, typename CompareT>
twomap<S,T,CompareS,CompareT>& twomap<S,T,CompareS,CompareT>::operator=(twomap<S,T,CompareS,CompareT>&& other) {
  // Move assignment operator.
  return twomap(std::forward<twomap<S,T,CompareS,CompareT>>(other));
}

template <typename S, typename T, typename CompareS, typename CompareT>
twomap<S,T,CompareS,CompareT>& twomap<S,T,CompareS,CompareT>::operator=(std::initializer_list<std::pair<S,T>> init) {
  /* This assignment operator replaces the contents of the twomap with the contents of the initializer
     list init.

     Note: for this operator, the list is a list of std::pair<S,T>.
  */  
  return twomap(init);
}

template <typename S, typename T, typename CompareS, typename CompareT>
twomap<S,T,CompareS,CompareT>& twomap<S,T,CompareS,CompareT>::operator=(std::initializer_list<std::pair<T,S>> init) {
    /* This assignment operator replaces the contents of the twomap with the contents of the initializer
     list init.

     Note: for this operator, the list is a list of std::pair<T,S>.
  */
  return twomap(init);
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename forward_map<S,T,CompareS>::iterator twomap<S,T,CompareS,CompareT>::S_begin() {
  // This method returns an iterator the beginning of the forward map.
  return map.begin();
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename inverse_map<T,S,CompareT>::iterator twomap<S,T,CompareS,CompareT>::T_begin() {
  // This method returns an iterator to the beginning of the inverse multimap.
  return inverse.begin();
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename forward_map<S,T,CompareS>::const_iterator twomap<S,T,CompareS,CompareT>::S_cbegin() {
  // This method returns a constant interator to the beginning of the forward map.
  return map.cbegin();
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename inverse_map<T,S,CompareT>::const_iterator twomap<S,T,CompareS,CompareT>::T_cbegin() {
  // This method returns a constant iterator to the beginning of the inverse multimap.
  return inverse.cbegin();
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename forward_map<S,T,CompareS>::iterator twomap<S,T,CompareS,CompareT>::S_end() {
  // This method returns an iterator to the end of the forward map.
  return map.end();
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename inverse_map<T,S,CompareT>::iterator twomap<S,T,CompareS,CompareT>::T_end() {
  // This method returns an iterator to the end of the inverse multimap.
  return inverse.end();
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename forward_map<S,T,CompareS>::const_iterator twomap<S,T,CompareS,CompareT>::S_cend() {
  // This method returns a constant iterator to the end of the forward map.
  return map.cend();
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename inverse_map<T,S,CompareT>::const_iterator twomap<S,T,CompareS,CompareT>::T_cend() {
  // This method returns a constant iterator to the end of the inverse multimap.
  return inverse.cend();
}

template <typename S, typename T, typename CompareS, typename CompareT>
bool twomap<S,T,CompareS,CompareT>::empty() {
  /* This method returns true if there are no elements in the twomap.

     It returns false otherwise.
  */
  return map.empty();
}

template <typename S, typename T, typename CompareS, typename CompareT>
size_t twomap<S,T,CompareS,CompareT>::size() {
  // This method returns the number of elements in the twomap.
  return map.size();
}

template <typename S, typename T, typename CompareS, typename CompareT>
size_t twomap<S,T,CompareS,CompareT>::max_size() {
  // This method returns the maximum number of elements that the twomap may hold.
  return std::min(map.max_size(),inverse.max_size());
}

template <typename S, typename T, typename CompareS, typename CompareT>
void twomap<S,T,CompareS,CompareT>::clear() {
  // This method erases all elements from the twomap.
  map.clear();
  inverse.clear();
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename std::pair<std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator>,bool> twomap<S,T,CompareS,CompareT>::insert(const std::pair<S,T>& value) {
  /* This method attempts to insert the key (S_key), value (T_key) pair into the twomap.
     
     The method returns a pair.
     
     If insertion was successful, then the first element of the pair is a pair of iterators
     corresponding to the position where the value pair was inserted into the forward map and the
     position where the value pair was inserted into the inverse map, in that order, or a pair of
     iterators corresponding to the position of the value in the forward map that prevented insertion
     and the position of the value in the inverse map that prevented insertion, in that order.

     The second element is a bool indicating whether the insertion was successful.

     Note: the type of the value in this method is std::pair<S,T>.
  */
  std::pair<typename forward_map<S,T,CompareS>::iterator,bool> iter = map.insert(value);
  typename inverse_map<T,S,CompareT>::iterator inv_iter;
  if (iter.second) {
    inv_iter = inverse.insert(std::make_pair(value.second,value.first));
  }
  else {
    /* Insertion into the forward map was unsuccessful.
       
       The location of the element in the inverse map corresponding to the element that prevented
       insertion in the forward map must be found.
    */
    auto er = inverse.equal_range(iter.first->second);
    auto it = er.first;
    bool found = false;
    while ((it != er.second) && !found) {
      if (it->second == value.first) {
	inv_iter = it;
	found = true;
      }
      else {
	++it;
      }
    }
  }
  return std::make_pair(std::make_pair(iter.first,inv_iter),iter.second);
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename std::pair<std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator>,bool> twomap<S,T,CompareS,CompareT>::insert(const std::pair<T,S>& value) {
    /* This method attempts to insert the key (T_key), value (S_key) pair into the twomap.
     
     The method returns a pair.
     
     If insertion was successful, then the first element of the pair is a pair of iterators
     corresponding to the position where the value pair was inserted into the forward map and the
     position where the value pair was inserted into the inverse map, in that order, or a pair of
     iterators corresponding to the position of the value in the forward map that prevented insertion
     and the position of the value in the inverse map that prevented insertion, in that order.

     The second element is a bool indicating whether the insertion was successful.

     Note: the type of the value in this method is std::pair<T,S>.
  */
  return insert(std::make_pair(value.second,value.first));
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename std::pair<std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator>,bool> twomap<S,T,CompareS,CompareT>::emplace(S&& key, T&& value) {
  /* This method attempts to construct an element in-place in the container using the provided key
     (S_key) and value (T_key).

     The method returns a pair.
     
     If emplacement was successful, then the first element of the pair is a pair of iterators
     corresponding to the position where the value pair was emplaced into the forward map and the
     position where the value pair was emplaced into the inverse map, in that order, or a pair of
     iterators corresponding to the position of the value in the forward map that prevented 
     emplacement and the position of the value in the inverse map that prevented emplacement, in that
     order.

     The second element is a bool indicating whether the emplacement was successful.

     Note: the key (S_key) comes before the value (T_key) in this method.
  */
  std::pair<typename forward_map<S,T,CompareS>::iterator,bool> iter = map.emplace(std::forward<S>(key),std::forward<T>(value));
  typename inverse_map<T,S,CompareT>::iterator inv_iter;
  if (iter.second) {
    S key_copy = iter.first->first;
    T val_copy = iter.first->second;
    inv_iter = inverse.emplace(val_copy,key_copy);
  }
  else {
    /* Emplacement into the forward map was unsuccessful.
       
       The location of the element in the inverse map corresponding to the element that prevented
       emplacement in the forward map must be found.
    */
    auto er = inverse.equal_range(iter.first->second);
    auto it = er.first;
    bool found = false;
    while ((it != er.second) && !found) {
      if (it->second == key) {
	inv_iter = it;
	found = true;
      }
      else {
	++it;
      }
    }
  }
  return std::make_pair(std::make_pair(iter.first,inv_iter),iter.second);
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename std::pair<std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator>,bool> twomap<S,T,CompareS,CompareT>::emplace(T&& value, S&& key) {
    /* This method attempts to construct an element in-place in the container using the provided value
     (T_key) and key (S_key).

     The method returns a pair.
     
     If emplacement was successful, then the first element of the pair is a pair of iterators
     corresponding to the position where the value pair was emplaced into the forward map and the
     position where the value pair was emplaced into the inverse map, in that order, or a pair of
     iterators corresponding to the position of the value in the forward map that prevented 
     emplacement and the position of the value in the inverse map that prevented emplacement, in that
     order.

     The second element is a bool indicating whether the emplacement was successful.

     Note: the value (T_key) comes before the key (S_key) in this method.
  */
  return emplace(std::forward<S>(key),std::forward<T>(value));
}


template <typename S, typename T, typename CompareS, typename CompareT>
std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator> twomap<S,T,CompareS,CompareT>::erase(typename forward_map<S,T,CompareS>::const_iterator pos) {
  /* This method removes the element in the forward map at position pos and removes the corresponding
     element in the inverse map.

     The method returns a pair containing an iterator following the removed element in the forward map
     and an iterator following the removed element in the inverse map, in that order.
  */
  auto r_iter = inverse.equal_range(pos->second);
  auto inv_iter = r_iter.first;
  // Find the specific element in the inverse map. (There may be many with the same value/T_key.)
  while ((inv_iter != r_iter.second) && (inv_iter->second != pos->first)) {
    inv_iter++;
  }
  assert(inv_iter != r_iter.second);
  // Erase from the inverse.
  inv_iter = inverse.erase(inv_iter);
  // Erase from the forward.
  auto iter = map.erase(pos);
  return std::make_pair(iter,inv_iter);
}

template <typename S, typename T, typename CompareS, typename CompareT>
std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator> twomap<S,T,CompareS,CompareT>::erase(typename inverse_map<T,S,CompareT>::const_iterator pos) {
  /* This method removes the element in the inverse map at position pos and removes the corresponding
     element in the forward map.

     The method returns a pair containing an iterator following the removed element in the forward map
     and an iterator following the removed element in the inverse map, in that order.
  */
  S S_value = pos->second;
  auto inv_iter = inverse.erase(pos);
  // Find and erase the corresponding element in the forward map.
  auto iter = map.erase(map.find(S_value));
  return std::make_pair(iter,inv_iter);
}

template <typename S, typename T, typename CompareS, typename CompareT>
std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator> twomap<S,T,CompareS,CompareT>::erase(typename forward_map<S,T,CompareS>::const_iterator first, typename forward_map<S,T,CompareS>::const_iterator last) {
  /* This method removes all elements in the forward map in the range defined by the iterators first
     and last. It also erases all elements in the inverse map corresponding to the elements found in
     the range defined by the iterators first and last.

     The method returns a pair containing an iterator following the last removed element in the
     forward map and an iterator following the last removed element in the inverse map, in that order.
  */
  auto iter = first;
  std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator> result;
  while (iter != last) {
    result = erase(iter++);
  }
  return result;
}

template <typename S, typename T, typename CompareS, typename CompareT>
std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator> twomap<S,T,CompareS,CompareT>::erase(typename inverse_map<T,S,CompareT>::const_iterator first, typename inverse_map<T,S,CompareT>::const_iterator last) {
  /* This method removes all elements in the inverse map in the range defined by the iterators first
     and last. It also erases all elements in the forward map corresponding to the elements found in
     the range defined by the iterators first and last.

     The method returns a pair containing an iterator following the last removed element in the
     forward map and an iterator following the last removed element in the inverse map, in that order.
  */
  auto iter = first;
  std::pair<typename forward_map<S,T,CompareS>::iterator,typename inverse_map<T,S,CompareT>::iterator> result;
  while (iter != last) {
    result = erase(iter++);
  }
  return result;
}

template <typename S, typename T, typename CompareS, typename CompareT>
size_t twomap<S,T,CompareS,CompareT>::erase(const S& key) {
  /* This method erases the element with the key (S_key) key in the twomap.

     The method returns a size_t indicating how many elements were removed (either 0 or 1 because the
     forward_map is not a multimap).

     Note: the key to be erased is an S_key.
  */
  // Find the position of the key in the forward map.
  auto iter = map.find(key);
  if (iter != map.end()) {
    // Erase at the position of the key.
    erase(iter);
    return 1;
  }
  return 0;
}

template <typename S, typename T, typename CompareS, typename CompareT>
size_t twomap<S,T,CompareS,CompareT>::erase(const T& key) {
  /* This method erases all elements with the key (T_key) key in the twomap.

     The method returns a size_t indicating how many elements were removed. 

     Note: the key to be erased is an T_key.
  */
  // Find all elements correspoding to key.
  auto r_iter = inverse.equal_range(key);
  if (r_iter.first != inverse.end()) {
    // std::distance may be used to compute the number of elments that will be removed.
    size_t distance = std::distance(r_iter.first,r_iter.second);
    // Erase all elements.
    erase(r_iter.first,r_iter.second);
    return distance;
  }
  return 0;
}

template <typename S, typename T, typename CompareS, typename CompareT>
void twomap<S,T,CompareS,CompareT>::swap(twomap<S,T,CompareS,CompareT>& other) {
  // This method swaps the contents of the twomap with those of another.
  std::swap(map,other.map);
  std::swap(inverse,other.inverse);
}

template <typename S, typename T, typename CompareS, typename CompareT>
twomap_setter<S,T,CompareS,CompareT> twomap<S,T,CompareS,CompareT>::at(const S& key) {
  /* at returns a twomap_setter that may be used to read and write to the value in the twomap
     with key (S_key) key.
     
     Unlike the [] operator, at throws an error if there is no element already in the twomap with
     the given key.
  */
  if (contains(key)) {
    return twomap_setter<S,T,CompareS,CompareT>(key,&map,&inverse);
  }
  else {
    throw std::out_of_range("Key not found.");
  }
}

template <typename S, typename T, typename CompareS, typename CompareT>
const twomap_setter<S,T,CompareS,CompareT> twomap<S,T,CompareS,CompareT>::at(const S& key) const {
  /* at returns a twomap_setter that may be used to read and write to the value in the twomap
     with key (S_key) key.
     
     Unlike the [] operator, at throws an error if there is no element already in the twomap with
     the given key.
  */
  if (contains(key)) {
    return twomap_setter<S,T,CompareS,CompareT>(key,&map,&inverse);
  }
  else {
    throw std::out_of_range("Key not found.");
  }
}

template <typename S, typename T, typename CompareS, typename CompareT>
twomap_setter<S,T,CompareS,CompareT> twomap<S,T,CompareS,CompareT>::operator[](const S& key) {
  /* The [] operator returns a twomap_setter that may be used to read and write to the value in the
     twomap with key (S_key) key.

     Note that if key is not already in the twomap, use of this operator inserts the key into the
     twomap, even if the value is not assigned.
  */
  return twomap_setter<S,T,CompareS,CompareT>(key,&map,&inverse);
}

template <typename S, typename T, typename CompareS, typename CompareT>
twomap_setter<S,T,CompareS,CompareT> twomap<S,T,CompareS,CompareT>::operator[](S&& key) {
  /* The [] operator returns a twomap_setter that may be used to read and write to the value in the
     twomap with key (S_key) key.

     Note that if key is not already in the twomap, use of this operator inserts the key into the
     twomap, even if the value is not assigned.
  */
  return twomap_setter<S,T,CompareS,CompareT>(std::forward<S>(key),&map,&inverse);
}

template <typename S, typename T, typename CompareS, typename CompareT>
size_t twomap<S,T,CompareS,CompareT>::count(const S& key) const {
  // This method returns the number of elements in the twomap with the given key (S_key).
  return map.count(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
size_t twomap<S,T,CompareS,CompareT>::count(const T& key) const {
  // This method returns the number of elements in the twomap with the given key (T_key).
  return inverse.count(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
template <typename K>
size_t twomap<S,T,CompareS,CompareT>::S_count(const K& key) const {
  // This method returns the number of elements in the twomap with the given key.
  // The key here must be comparable with elements of type S using CompareS.
  return map.count(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
template <typename K>
size_t twomap<S,T,CompareS,CompareT>::T_count(const K& key) const {
  // This method returns the number of elements in the twomap with the given key.
  // The key here must be comparable with elements of type T using CompareT.
  return inverse.count(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename forward_map<S,T,CompareS>::iterator twomap<S,T,CompareS,CompareT>::find(const S& key) {
  /* This method finds the element in the twomap with key (S_key) key, if it exists, and returns an
     iterator positioned at the element in the forward map.

     Otherwise, this method returns an iterator to the end of the forward map.
  */
  return map.find(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename inverse_map<T,S,CompareT>::iterator twomap<S,T,CompareS,CompareT>::find(const T& key) {
  /* This method finds the first element in the twomap with key (T_key) key, if it exists, and returns
     an iterator positioned at the element in the inverse map.
     
     Otherwise, this method returns an iterator to the end of the inverse map.
  */
  return inverse.find(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename forward_map<S,T,CompareS>::const_iterator twomap<S,T,CompareS,CompareT>::find(const S& key) const {
  /* This method finds the element in the twomap with key (S_key) key, if it exists, and returns a
     constant iterator positioned at the element in the forward map.

     Otherwise, this method returns a constant iterator to the end of the forward map.
  */
  return map.find(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename inverse_map<T,S,CompareT>::const_iterator twomap<S,T,CompareS,CompareT>::find(const T& key) const {
  /* This method finds the first element in the twomap with key (T_key) key, if it exists, and returns
     a constant iterator positioned at the element in the inverse map.
     
     Otherwise, this method returns a constant iterator to the end of the inverse map.
  */
  return inverse.find(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
template <typename K>
typename forward_map<S,T,CompareS>::iterator twomap<S,T,CompareS,CompareT>::S_find(const K& key) {
  /* This method finds the element in the twomap with the given key, if it exists, and returns an
     iterator positioned at the element in the forward map.

     Otherwise, this method returns an iterator to the end of the forward map.

     The key here must be comparable with elements of type S using CompareS.
  */
  return map.find(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
template <typename K>
typename inverse_map<T,S,CompareT>::iterator twomap<S,T,CompareS,CompareT>::T_find(const K& key) {
  /* This method finds the element in the twomap with the given key, if it exists, and returns an
     iterator positioned at the element in the inverse map.

     Otherwise, this method returns an iterator to the end of the inverse map.

     The key here must be comparable with elements of type T using CompareT.
  */
  return inverse.find(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
template <typename K>
typename forward_map<S,T,CompareS>::iterator twomap<S,T,CompareS,CompareT>::S_find(const K& key) const {
  /* This method finds the element in the twomap with the given key, if it exists, and returns a
     constant iterator positioned at the element in the forward map.

     Otherwise, this method returns a constant iterator to the end of the forward map.

     The key here must be comparable with elements of type S using CompareS.
  */
  return map.find(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
template <typename K>
typename inverse_map<T,S,CompareT>::iterator twomap<S,T,CompareS,CompareT>::T_find(const K& key) const {
  /* This method finds the element in the twomap with the given key, if it exists, and returns a
     constant iterator positioned at the element in the inverse map.

     Otherwise, this method returns a constant iterator to the end of the inverse map.

     The key here must be comparable with elements of type T using CompareT.
  */
  return inverse.find(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
bool twomap<S,T,CompareS,CompareT>::contains(const S& key) const {
  // This method returns true when the twomap contains the key (S_key) key.
  return map.find(key) != map.end();
}

template <typename S, typename T, typename CompareS, typename CompareT>
bool twomap<S,T,CompareS,CompareT>::contains(const T& key) const {
  // This method returns true when the twomap contains the key (T_key) key.
  return inverse.find(key) != inverse.end();
}

template <typename S, typename T, typename CompareS, typename CompareT>
template <typename K>
bool twomap<S,T,CompareS,CompareT>::S_contains(const K& key) const {
  // This method returns true when the twomap contains the given key.
  // The key here must be comparable with elements of type S using CompareS.
  return map.find(key) != map.end();
}

template <typename S, typename T, typename CompareS, typename CompareT>
template <typename K>
bool twomap<S,T,CompareS,CompareT>::T_contains(const K& key) const {
  // This method returns true when the twomap contains the given key.
  // The key here must be comparable with elements of type T using CompareT.
  return inverse.find(key) != inverse.end();
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename std::pair<typename forward_map<S,T,CompareS>::iterator,typename forward_map<S,T,CompareS>::iterator> twomap<S,T,CompareS,CompareT>::equal_range(const S& key) {
  /* This method returns a pair of iterators positioned at the beginning and end (in that order) of
     a range of elements in the forward map containing elements with keys equal to the given key
     (S_key) key.

     If no such elements exist, both elements of the pair will be iterators positioned at the end of
     the forward map.
  */
  return map.equal_range(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename std::pair<typename inverse_map<T,S,CompareT>::iterator,typename inverse_map<T,S,CompareT>::iterator> twomap<S,T,CompareS,CompareT>::equal_range(const T& key) {
  /* This method returns a pair of iterators positioned at the beginning and end (in that order) of
     a range of elements in the inverse map containing elements with keys equal to the given key
     (T_key) key.

     If no such elements exist, both elements of the pair will be iterators positioned at the end of
     the inverse map.
  */
  return inverse.equal_range(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename std::pair<typename forward_map<S,T,CompareS>::const_iterator,typename forward_map<S,T,CompareS>::const_iterator> twomap<S,T,CompareS,CompareT>::equal_range(const S& key) const {
  /* This method returns a pair of constant iterators positioned at the beginning and end (in that
     order) of a range of elements in the forward map containing elements with keys equal to the
     given key (S_key) key.
     
     If no such elements exist, both elements of the pair will be constant iterators positioned at the
     end of the forward map.
  */
  return map.equal_range(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
typename std::pair<typename inverse_map<T,S,CompareT>::const_iterator,typename inverse_map<T,S,CompareT>::const_iterator> twomap<S,T,CompareS,CompareT>::equal_range(const T& key) const {
  /* This method returns a pair of constant iterators positioned at the beginning and end (in that
     order) of a range of elements in the inverse map containing elements with keys equal to the
     given key (T_key) key.
     
     If no such elements exist, both elements of the pair will be constant iterators positioned at the
     end of the inverse map.
  */
  return inverse.equal_range(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
template <typename K>
typename std::pair<typename forward_map<S,T,CompareS>::iterator,typename forward_map<S,T,CompareS>::iterator> twomap<S,T,CompareS,CompareT>::S_equal_range(const K& key) {
  /* This method returns a pair of iterators positioned at the beginning and end (in that order) of
     a range of elements in the forward map containing elements with keys equal to the given key.

     If no such elements exist, both elements of the pair will be iterators positioned at the end of
     the forward map.

     The key here must be comparable with elements of type S using CompareS.
  */
  return map.equal_range(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
template <typename K>
typename std::pair<typename inverse_map<T,S,CompareT>::const_iterator,typename inverse_map<T,S,CompareT>::const_iterator> twomap<S,T,CompareS,CompareT>::T_equal_range(const K& key) {
   /* This method returns a pair of iterators positioned at the beginning and end (in that order) of
     a range of elements in the inverse map containing elements with keys equal to the given key.

     If no such elements exist, both elements of the pair will be iterators positioned at the end of
     the inverse map.

     The key here must be comparable with elements of type T using CompareT.
  */
  return inverse.equal_range(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
template <typename K>
typename std::pair<typename forward_map<S,T,CompareS>::iterator,typename forward_map<S,T,CompareS>::iterator> twomap<S,T,CompareS,CompareT>::S_equal_range(const K& key) const {
  /* This method returns a pair of constant iterators positioned at the beginning and end (in that
     order) of a range of elements in the forward map containing elements with keys equal to the
     given key.

     If no such elements exist, both elements of the pair will be constant iterators positioned at
     the end of the forward map.

     The key here must be comparable with elements of type S using CompareS.
  */
  return map.equal_range(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
template <typename K>
typename std::pair<typename inverse_map<T,S,CompareT>::const_iterator,typename inverse_map<T,S,CompareT>::const_iterator> twomap<S,T,CompareS,CompareT>::T_equal_range(const K& key) const {
  /* This method returns a pair of constant iterators positioned at the beginning and end (in that
     order) of a range of elements in the inverse map containing elements with keys equal to the
     given key.

     If no such elements exist, both elements of the pair will be constant iterators positioned at
     the end of the inverse map.

     The key here must be comparable with elements of type T using CompareT.
  */
  return inverse.equal_range(key);
}

template <typename S, typename T, typename CompareS, typename CompareT>
bool operator==(const twomap<S,T,CompareS,CompareT>& lhs, const twomap<S,T,CompareS,CompareT>& rhs) {
  return lhs.map == rhs.map;
}

template <typename S, typename T, typename CompareS, typename CompareT>
bool operator!=(const twomap<S,T,CompareS,CompareT>& lhs, const twomap<S,T,CompareS,CompareT>& rhs) {
  return lhs.map != rhs.map;
}

namespace std {
  template <typename S, typename T, typename CompareS, typename CompareT>
  void swap(twomap<S,T,CompareS,CompareT> &a, twomap<S,T,CompareS,CompareT> &b) {
    a.swap(b);
  }
}
