
template <int L, int R, int N>
struct IsSquareHelper {
  static const int M = (L + R) / 2;
  static const bool value = M * M < N ? IsSquareHelper<M + 1, R, N>::value : IsSquareHelper<L, M, N>::value;
};

template <int M, int N>
struct IsSquareHelper<M, M, N> {
  static const bool value = M * M == N;
};

template <int N>
struct IsSquare {
  static const bool value = IsSquareHelper<0, N, N>::value;
};

template <int N>
const bool is_square = IsSquare<N>::value;

int main() {
  static_assert(is_square<1> == true);
  static_assert(is_square<2> == false);
  static_assert(is_square<3> == false);
  static_assert(is_square<4> == true);
  static_assert(is_square<9> == true);
  static_assert(is_square<100> == true);
  static_assert(is_square<101> == false);
  return 0;
}