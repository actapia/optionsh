#ifndef TWOMAP_SETTER_H
#define TWOMAP_SETTER_H

#include <cstring>
#include <iostream>
#include <unordered_map>
#include "different_concept.h"
#include "twomap.h"
#include "map_defs.h"

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

/* Most of the compound operators have identical workings, so this macro is used to define them.
   
   A compound operator op= compute op with the right hand side and the current value in the twomap for
   the twomap_setter's key and sets the value corresponding to the twomap_setter's key to the result.
*/
#define SIMPLE_COMPOUND_OPERATOR(op) template <typename S, typename T, typename CompareS, typename CompareT> T& twomap_setter<S,T,CompareS,CompareT>::operator op (const T& other) { inverse_delete(other); T& result = (*map)[key] op other; inverse->emplace(result,key); return result;}

//static_assert(strcmp(__FILE__,"twomap_setter.cpp") != 0, "Do not compile this file.");

template <typename S, typename T, typename CompareS, typename CompareT>
twomap_setter<S,T,CompareS,CompareT>::twomap_setter(S&& mk, forward_map<S,T,CompareS>* mp, inverse_map<T,S,CompareT>* inv): key(mk),										      
														   map(mp),
														   inverse(inv) {
};

template <typename S, typename T, typename CompareS, typename CompareT>
twomap_setter<S,T,CompareS,CompareT>::twomap_setter(const S& mk, forward_map<S,T,CompareS>* mp, inverse_map<T,S,CompareT>* inv): key(mk),										      
														   map(mp),
														   inverse(inv) {
};

template <typename S, typename T, typename CompareS, typename CompareT>
void twomap_setter<S,T,CompareS,CompareT>::inverse_delete(const T& other) const {
  // This method deletes the pair (key,other) from the twomap's inverse.
  typename forward_map<S,T,CompareS>::const_iterator current_val = map->find(key);
  if (current_val != map->end()) {
    // Find the exact value.
    auto iters = inverse->equal_range(current_val->second);
    auto it = iters.first;
    while (it != iters.second) {
      if (it->second == current_val->first)
	// Erase the value.
	inverse->erase(it++);
      else
	it++;
    }
  }
}

template <typename S, typename T, typename CompareS, typename CompareT>
T& twomap_setter<S,T,CompareS,CompareT>::set(const T& other) const {
  // This method sets the value corresponding to key in the twomap to other.
  inverse_delete(other);
  inverse->emplace(other,key);
  return (*map)[key] = other;
}

template <typename S, typename T, typename CompareS, typename CompareT>
T& twomap_setter<S,T,CompareS,CompareT>::operator=(const T& other) {
  // This operator sets the value corresponding to key in the twomap to other.
  return set(other);
};

template <typename S, typename T, typename CompareS, typename CompareT>
T& twomap_setter<S,T,CompareS,CompareT>::operator=(const twomap_setter<S,T,CompareS,CompareT>& other) {
  // This operator sets the value corresponding to key in the twomap to the value corresponding to the
  // key of other in other's twomap.
  return set((*other.map)[other.key]);
};

template <typename S, typename T, typename CompareS, typename CompareT>
T twomap_setter<S,T,CompareS,CompareT>::operator+(const T& other) {
  // This operator adds the value corresponding to key in the twomap to other and returns the result.
  return (*map)[key] + other;
}

template <typename S, typename T, typename CompareS, typename CompareT>
T twomap_setter<S,T,CompareS,CompareT>::operator-(const T& other) {
  // This operator subtracts other from the value corresponding to key in the twomap and returns the
  // result.
  return (*map)[key] - other;
}

template <typename S, typename T, typename CompareS, typename CompareT>
T twomap_setter<S,T,CompareS,CompareT>::operator*(const T& other) {
  // This operator multiplies the value corresponding to key in the twomap by other and returns the
  // result.
  return (*map)[key] * other;
}

template <typename S, typename T, typename CompareS, typename CompareT>
T twomap_setter<S,T,CompareS,CompareT>::operator/(const T& other) {
  // This operator divides the value corresponding to key in the twomap by other and returns the
  // result.
  return (*map)[key] / other;
}

template <typename S, typename T, typename CompareS, typename CompareT>
T twomap_setter<S,T,CompareS,CompareT>::operator%(const T& other) {
  // This operator computes the value corresponding to key in the twomap modulo other and returns
  // the result.
  return (*map)[key] % other;
}

template <typename S, typename T, typename CompareS, typename CompareT>
T twomap_setter<S,T,CompareS,CompareT>::operator+() {
  // This operator applies the unary + operator to the value corresponding to key in the twomap
  // and returns the result.
  return +(*map)[key];
}

template <typename S, typename T, typename CompareS, typename CompareT>
T twomap_setter<S,T,CompareS,CompareT>::operator-() {
  // This operator negates the value corresponding to key in the twomap and returns the result.
  return -(*map)[key];
}

template <typename S, typename T, typename CompareS, typename CompareT>
T twomap_setter<S,T,CompareS,CompareT>::operator++(int) {
  // The operator increments the value corresponding to key in the twomap and returns the result
  // before incrementing.
  T old_value = (*map)[key];
  set((*map)[key] + 1);
  return old_value;
}

template <typename S, typename T, typename CompareS, typename CompareT>
twomap_setter<S,T,CompareS,CompareT>& twomap_setter<S,T,CompareS,CompareT>::operator++() {
  // The operator increments the value corresponding to key in the twomap and returns the result
  // after incrementing.
  set((*map)[key] + 1);
  return *this;
}

template <typename S, typename T, typename CompareS, typename CompareT>
T twomap_setter<S,T,CompareS,CompareT>::operator--(int) {
  // The operator decrements the value corresponding to key in the twomap and returns the result
  // before decrementing.
  T old_value = (*map)[key];
  set((*map)[key] - 1);
  return old_value;
}

template <typename S, typename T, typename CompareS, typename CompareT>
twomap_setter<S,T,CompareS,CompareT>& twomap_setter<S,T,CompareS,CompareT>::operator--() {
  // The operator decrements the value corresponding to key in the twomap and returns the result
  // after decrementing.
  set((*map)[key] - 1);
  return *this;
}

template <typename S, typename T, typename CompareS, typename CompareT>
bool twomap_setter<S,T,CompareS,CompareT>::operator==(const T& other) const{
  // This operator compares the value corresponding to key in the twomap to other and returns the
  // true when they are equal.
  return (*map)[key] == other;
}

template <typename S, typename T, typename CompareS, typename CompareT>
bool twomap_setter<S,T,CompareS,CompareT>::operator!=(const T& other) const{
  // This operator compares the value corresponding to key in the twomap to other and returns the
  // true when they are not equal.
  return (*map)[key] != other;
}

template <typename S, typename T, typename CompareS, typename CompareT>
bool twomap_setter<S,T,CompareS,CompareT>::operator<(const T& other) const {
  // This operator compares the value corresponding to key in the twomap to other and returns the
  // true when the former is less than the latter.
  return (*map)[key] < other;
}

template <typename S, typename T, typename CompareS, typename CompareT>
bool twomap_setter<S,T,CompareS,CompareT>::operator>(const T& other) const {
  // This operator compares the value corresponding to key in the twomap to other and returns the
  // true when the former is greater than the latter.
  return (*map)[key] > other;
}

template <typename S, typename T, typename CompareS, typename CompareT>
bool twomap_setter<S,T,CompareS,CompareT>::operator>=(const T& other) const {
  // This operator compares the value corresponding to key in the twomap to other and returns the
  // true when the former is greater than or equal to the latter.
  return (*map)[key] >= other;
}

template <typename S, typename T, typename CompareS, typename CompareT>
bool twomap_setter<S,T,CompareS,CompareT>::operator<=(const T& other) const {
  // This operator compares the value corresponding to key in the twomap to other and returns the
  // true when the former is less than or equal to the latter.
  return (*map)[key] <= other;
}

template <typename S, typename T, typename CompareS, typename CompareT>
bool twomap_setter<S,T,CompareS,CompareT>::operator!() const {
  // This operator computes the boolean inverse of the value corresponding to key in the twomap and
  // returns the result.
  return !(*map)[key];
}

template <typename S, typename T, typename CompareS, typename CompareT>
bool twomap_setter<S,T,CompareS,CompareT>::operator&&(const T& other) const {
  // This operator computes the value corresponding to key in the twomap and other and returns the
  // result.
  return (*map)[key] && other;
}

template <typename S, typename T, typename CompareS, typename CompareT>
bool twomap_setter<S,T,CompareS,CompareT>::operator||(const T& other) const {
  // This operator computes the value corresponding to key in the twomap or other and returns the
  // result.
  return (*map)[key] || other;
}

template <typename S, typename T, typename CompareS, typename CompareT>
T twomap_setter<S,T,CompareS,CompareT>::operator~() {
  // This operator computes the bitwise inverse of the value corresponding to key in the twomap and
  // returns the result.
  return ~(*map)[key];
}

template <typename S, typename T, typename CompareS, typename CompareT>
T twomap_setter<S,T,CompareS,CompareT>::operator&(const T& other) {
  // This operator computes the bitwise and of the value corresponding to key in the twomap and other
  // and returns the result.
  return (*map)[key] & other;
}

template <typename S, typename T, typename CompareS, typename CompareT>
T twomap_setter<S,T,CompareS,CompareT>::operator|(const T& other) {
  // This operator computes the bitwise or of the value corresponding to key in the twomap and other
  // and returns the result.
  return (*map)[key] | other;
}

template <typename S, typename T, typename CompareS, typename CompareT>
T twomap_setter<S,T,CompareS,CompareT>::operator^(const T& other) {
  // This operator computes the bitwise exclusive or of the value corresponding to key in the twomap
  // and other and returns the result.
  return (*map)[key] ^ other;
}

template <typename S, typename T, typename CompareS, typename CompareT>
T twomap_setter<S,T,CompareS,CompareT>::operator<<(const T& other) {
  // This operator left shifts the value corresponding to key in the twomap by other and returns the
  // result.
  return (*map)[key] << other;
}

template <typename S, typename T, typename CompareS, typename CompareT>
T twomap_setter<S,T,CompareS,CompareT>::operator>>(const T& other) {
  // This operator right shifts the value corresponding to key in the twomap by other and returns the
  // result.
  return (*map)[key] >> other;
}

// I got tired of writing these functions out.
// See the macro above.

SIMPLE_COMPOUND_OPERATOR(+=);
SIMPLE_COMPOUND_OPERATOR(-=);
SIMPLE_COMPOUND_OPERATOR(*=);
SIMPLE_COMPOUND_OPERATOR(/=);
SIMPLE_COMPOUND_OPERATOR(%=);
SIMPLE_COMPOUND_OPERATOR(&=);
SIMPLE_COMPOUND_OPERATOR(|=);
SIMPLE_COMPOUND_OPERATOR(^=);
SIMPLE_COMPOUND_OPERATOR(<<=);
SIMPLE_COMPOUND_OPERATOR(>>=);

// template <typename S, typename T, typename CompareS, typename CompareT>
// auto twomap_setter<S,T,CompareS,CompareT>::operator[](S& index) {
//   return (*map)[key][index];
// }

// template <typename S, typename T, typename CompareS, typename CompareT>
// auto twomap_setter<S,T,CompareS,CompareT>::operator*() {
//   return *((*map)[key]);
// }

template <typename S, typename T, typename CompareS, typename CompareT>
twomap_setter<S,T,CompareS,CompareT>::operator T() {
  // This operator converts the value corresponding to key in the twomap to type T and returns the
  // result.
  return (*map)[key];
}

template <typename S, typename T, typename CompareS, typename CompareT>
std::ostream& operator<<(std::ostream& os, const twomap_setter<S,T,CompareS,CompareT>& setter) {
  // This operator writes the value corresponding to setter's key in its twomap to an output stream.
  return os << (*setter.map)[setter.key];
}

template <typename S, typename T, typename CompareS, typename CompareT>
std::istream& operator>>(std::istream& os, const twomap_setter<S,T,CompareS,CompareT>& setter) {
  // This operator read into the value corresponding to setter's key in its twomap from
  // an output stream.
  T value;
  os >> value;
  // setter.inverse->emplace(value,setter.key);
  // (*setter.map)[setter.key] = value;
  setter.set(value);
  return os;
}

#endif
