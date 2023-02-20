
template <int L, int R, int N>
struct SqrtHelper {
  static const int M = (L + R) / 2;
  static const int value = M * M < N ? SqrtHelper<M + 1, R, N>::value : SqrtHelper<L, M, N>::value;
};

template <int M, int N>
struct SqrtHelper<M, M, N> {
  static const int value = M;
};

template <int N>
struct SqrtUpperBound {
  static const int value = SqrtHelper<0, N, N>::value;
};

template <int N>
const int sqrt_upper_bound = SqrtUpperBound<N>::value;

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
  static const bool value = IsPrimeHelper<N, sqrt_upper_bound<N>>::value;
};

template <>
struct IsPrime<1>{
  static const bool value = false;
};

template <>
struct IsPrime<2>{
  static const bool value = true;
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
  static_assert(is_prime<8> == false);
  static_assert(is_prime<9> == false);
  static_assert(is_prime<10> == false);
  static_assert(is_prime<11>);
  static_assert(is_prime<12> == false);
  static_assert(is_prime<13>);
  static_assert(!is_prime<14>);
  static_assert(!is_prime<15>);
  static_assert(is_prime<16> == false);
  static_assert(is_prime<113> == true);
  return 0;
}