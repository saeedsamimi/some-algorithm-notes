#include "./BigInt.hpp"
#include <chrono>

using namespace std;

typedef pair<BigInt, BigInt> FastPair;
#define a first
#define b second

FastPair FastDoubling(int n) {
  if (n == 0)
    return {0, 1};
  FastPair t = FastDoubling(n / 2);
  // As F(2n) = F(n)[2F(n+1) – F(n)]
  BigInt c = t.a * (2 * t.b - t.a);
  // As F(2n + 1) = F(n)^2 + F(n+1)^2
  BigInt d = t.a * t.a + t.b * t.b;
  // Check if N is odd or even
  if (n % 2)
    return {d, c + d};
  return {c, d};
}

int main() {
  int n;
  cin >> n;
  auto start = chrono::high_resolution_clock::now();
  cout << "Answer: " << FastDoubling(n).first << endl;
  auto end = chrono::high_resolution_clock::now();
  cout << "Time: \t"
       << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
       << " ns" << endl;
  return 0;
}
