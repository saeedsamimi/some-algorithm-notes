#include <stdio.h>

int array[1000000];

char analyze(int n, int k) {
  //const int max = n - k + 1;
  int length = 0, min = 1000000000;
  for (int i = 0; i < n; i++) {
    if (array[i]) {
      length++;
      if (array[i] < min)
        min = array[i];
    } else {
      length = 0;
      min = 1000000000;
    }
    if (length == k) {
      int nextStart = -1;
      for (int minPosition = i - k + 1; minPosition <= i; minPosition++)
        if (!(array[minPosition] -= min))
          nextStart = minPosition;
      i = nextStart;
      length = 0;
      min = 1000000000;
    }
  }
  for (int i = n - 1; i >= 0; i--)
    if (array[i]) return 0;
  return 1;
}

int main() {
  int t;
  scanf("%d", &t);
  int n, k;
  for (int i = 0; i < t; i++) {
    scanf("%d %d", &n, &k);
    for (int j = 0; j < n; j++)
      scanf("%d", array + j); // equals = &array[j]
    printf(analyze(n, k) ? "Cake\n" : "Fake\n");
  }
  return 0;
}