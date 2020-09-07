#ifndef MAP_DEFS_H
#define MAP_DEFS_H

#include <map>

template <typename S, typename T, typename Compare = std::less<S>>
using forward_map = std::map<S,T,Compare>;

template <typename S, typename T, typename Compare = std::less<S>>
using inverse_map = std::multimap<S,T,Compare>;

#endif
