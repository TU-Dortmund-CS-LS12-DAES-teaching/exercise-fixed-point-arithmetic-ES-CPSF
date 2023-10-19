#include <type_traits>

template <class T, class U> struct AreSameTemplate : std::is_same<T, U> {};

template <template <class...> class T, class T1, class T2>
struct AreSameTemplate<T<T1>, T<T2>> : std::true_type {};

template <class T, class U> constexpr bool checkTypes(T, U) {
  return AreSameTemplate<T, U>::value;
}
