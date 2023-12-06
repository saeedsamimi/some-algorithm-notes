#include <stdio.h>

int DivisorsCount(int n) {
  int k = 0;
  while (!(n % 2)) {
    n /= 2;
    k++;
  }
  int p = (k + 1);
  for (int i = 3; n > 1; i += 2) {
    k = 0;
    while (!(n % i)) {
      n /= i;
      k++;
    }
    p *= (k + 1);
  }
  return p;
}

int main() {
  int n;
  scanf("%d", &n);
  printf("%d", DivisorsCount(n));
  return 0;
}