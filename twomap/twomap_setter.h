#ifndef TWOMAP_SETTER_H
#define TWOMAP_SETTER_H

#include <iostream>
#include <unordered_map>
#include "different_concept.h"
#include "twomap.h"

template <typename S, typename T, typename CompareS, typename CompareT>
#ifdef __cpp_concepts
requires different<S,T>
#endif
class twomap_setter {
  /* twomap_setter is a proxy object used for accessing and setting elements of a twomap using the
     [] operator or the at method.

     This class is necessary because additional logic is required for setting elements in a twomap;
     it is necessary to change both the twomap's forward and inverse maps when setting.

     Unfortunately, the proxy object is not perfectly transparent. For example, accessing members
     of a struct through a twomap_setter is impossible. (Though it may be possible in the future if
     dot operator overloading is added to the language.)
  */
public:
  twomap_setter(S&& mk, forward_map<S,T,CompareS>* mp, inverse_map<T,S,CompareT>* inv);
  twomap_setter(const S& mk, forward_map<S,T,CompareS>* mp, inverse_map<T,S,CompareT>* inv);
  // Assignment
  T& operator=(const T& other);
  T& operator=(const twomap_setter<S,T,CompareS,CompareT>& other);
  // Arithmetic
  T operator+(const T& other);
  T operator-(const T& other);
  T operator*(const T& other);
  T operator/(const T& other);
  T operator%(const T& other);
  T operator+();
  T operator-();
  T operator++(int);
  twomap_setter<S,T,CompareS,CompareT>& operator++();
  T operator--(int);
  twomap_setter<S,T,CompareS,CompareT>& operator--();
  // Comparison
  bool operator==(const T& other) const;
  bool operator!=(const T& other) const;
  bool operator>(const T& other) const;
  bool operator<(const T& other) const;
  bool operator>=(const T& other) const;
  bool operator<=(const T& other) const;
  // Logic
  bool operator!() const;
  bool operator&&(const T& other) const;
  bool operator||(const T& other) const;
  // Bitwise
  T operator~();
  T operator&(const T& other);
  T operator|(const T& other);
  T operator^(const T& other);
  T operator<<(const T& other);
  T operator>>(const T& other);
  // Compound
  T& operator+=(const T& other);
  T& operator-=(const T& other);
  T& operator*=(const T& other);
  T& operator/=(const T& other);
  T& operator%=(const T& other);
  T& operator&=(const T& other);
  T& operator|=(const T& other);
  T& operator^=(const T& other);
  T& operator<<=(const T& other);
  T& operator>>=(const T& other);
  // Member/pointer
  // Cast
  operator T();
  // I/O
  template <class U, class V, class CompareU, class CompareV>
  friend std::ostream& operator<<(std::ostream& os, const twomap_setter<U,V,CompareU,CompareV>& setter);
  template <class U, class V, class CompareU, class CompareV>
  friend std::istream& operator>>(std::istream& os, const twomap_setter<U,V,CompareU,CompareV>& setter);
private:
  // key is the key the setter used to access/mutate the parent twomap
  S key;
  // map is a pointer to the parent twomap's forward map.
  forward_map<S,T,CompareS>* map;
  // inverse is a pointer to the parent twomap's inverse map;
  inverse_map<T,S,CompareT>* inverse;
  T& set(const T& other) const;
  void inverse_delete(const T& other) const;
};

#include "twomap_setter.cpp"


#endif
