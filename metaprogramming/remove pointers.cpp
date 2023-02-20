#include <vector>

template <typename T>
struct remove_pointer {
  using type = T;
  static const bool is_pointer = false;
};

template <typename T>
struct remove_pointer<T*> {
  using type = T;
  static const bool is_pointer = true;
};

template <typename T>
using remove_pointer_t = typename remove_pointer<T>::type;

template <typename T>
struct remove_all_pointers_helper {
  static const bool is_pointer = remove_pointer<T>::is_pointer;
  using type = T;
};

template <typename T>
struct remove_all_pointers_helper<T*> {
  static const bool is_pointer = remove_pointer<T>::is_pointer;
  using type = typename remove_all_pointers_helper<typename remove_pointer<T>::type>::type;
};

template <typename T>
struct remove_all_pointers {
  using type = typename std::conditional<remove_all_pointers_helper<T>::is_pointer,
               typename remove_all_pointers_helper<T>::type, T>::type;
};

template <typename T>
using remove_all_pointers_t = typename remove_all_pointers<T>::type;

int main() {
  static_assert(std::is_same<remove_pointer_t<int*>, int>());
  static_assert(!std::is_same<remove_pointer_t<int**>, int>());
  static_assert(std::is_same<remove_all_pointers_t<int****>, int>());
  static_assert(!std::is_same<remove_all_pointers_t<int****>, int**>());
  static_assert(std::is_same<remove_all_pointers_t<int*******>, int>());
  static_assert(std::is_same<remove_all_pointers_t<int>, int>());
  return 0;
}