#include <iostream>
#include <chrono>

using namespace std;

const int maxn = 100;
typedef long long ll;

struct mat2D {
  ll a11, a12, a21, a22;
} const fibonacci_mat{1, 1, 1, 0};

mat2D mat_power2(const mat2D &m) {
  return {m.a11 * m.a11 + m.a12 * m.a21,
          m.a11 * m.a12 + m.a12 * m.a22,
          m.a21 * m.a11 + m.a22 * m.a21,
          m.a21 * m.a12 + m.a22 * m.a22};
}

mat2D mat_prod(const mat2D &m1, const mat2D &m2) {
  return {m1.a11 * m2.a11 + m1.a12 * m2.a21,
          m1.a11 * m2.a12 + m1.a12 * m2.a22,
          m1.a21 * m2.a11 + m1.a22 * m2.a21,
          m1.a21 * m2.a12 + m1.a22 * m2.a22};
}

mat2D fib_util(int n) {
  if (n < 2)
    return fibonacci_mat;
  mat2D mat = fibonacci_mat;
  int k = 1;
  while (k < n) {
    k *= 2;
    if (k <= n)
      mat = mat_power2(mat);
    else {
      k /= 2;
      break;
    }
  }
  return n == k ? mat : mat_prod(fib_util(n - k), mat);
}

ll fib_mat2d(int n) {
  return fib_util(n).a11;
}

ll fib_rec(int n) {
  if (n < 2) return 1;
  return fib_rec(n - 1) + fib_rec(n - 2);
}

void fib_measure(int n, ll func(int)) {
  auto start = chrono::high_resolution_clock::now();
  ll fib_temp = func(n);
  auto end = chrono::high_resolution_clock::now();
  printf("%lld \t Time: %ld (ns)\n",
         fib_temp,
         chrono::duration_cast<chrono::nanoseconds>(end - start).count());
}

ll dp[maxn]{1, 1};

ll fib_dp(int n) {
  return dp[n] ? dp[n] : dp[n] = fib_dp(n - 1) + fib_dp(n - 2);
}

ll fib_simple(int n) {
  ll a = 1, b = 1;
  for (int i = 1; i < n; i++) {
    ll temp = a + b;
    a = b;
    b = temp;
  }
  return b;
}

int main() {
  int n;
  cin >> n;
  // the best choose is fib_simple ,
  // and after that the fib_dp and after that fib_mat2d and the worst algorithm is fib_rec
  
  // example output for n = 40
  //  40
  //  165580141        Time: 495896000 (ns) -> fib_rec
  //  165580141        Time: 1200 (ns) -> fib_mat2d
  //  165580141        Time: 200 (ns) -> fib_simple
  //  165580141        Time: 700 (ns) -> fib_dp
  for (auto func: {fib_mat2d, fib_simple, fib_dp})
    fib_measure(n, func);
}