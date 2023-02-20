
template <int N, int D>
struct IsPrimeHelper {
  static const bool value = N % D != 0 && IsPrimeHelper<N, D - 1>::value;
};

template <int N>
struct IsPrimeHelper<N, 1> {
  static const bool value = true;
};

template <int N>
struct IsPrimeHelper<N, 0> {
  static const bool value = false;
};

template <int N>
struct IsPrime {
  static const bool value = IsPrimeHelper<N, N - 1>::value;
};

template <int N>
const bool is_prime = IsPrime<N>::value;

int main() {
  static_assert(is_prime<1> == false);
  static_assert(is_prime<2> == true);
  static_assert(is_prime<3> == true);
  static_assert(is_prime<4> == false);
  static_assert(is_prime<5> == true);
  static_assert(is_prime<6> == false);
  static_assert(is_prime<7> == true);
  static_assert(is_prime<113> == true);
  return 0;
}