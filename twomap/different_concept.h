#ifndef DIFFERENT_CONCEPT
#define DIFFERENT_CONCEPT

#ifdef __cpp_concepts
// When required, different ensures that it is not possible to convert between the two types in the
// template.
template <typename S, typename T>
concept different = !std::is_convertible<S,T>::value && !std::is_convertible<T,S>::value;
#endif

#endif
