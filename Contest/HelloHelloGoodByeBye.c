#include <stdio.h>

int main() {
  int n;
  scanf("%d", &n);
  char names[50][50];
  for (int i = 0; i < n; i++)
    scanf("%s", names[i]);
  for (int i = 1; i < n; i++)
    for (int j = i-1; j>=0; j--)
      printf("%s: salam %s!\n", names[i], names[j]);
  for (int i = 0; i < n; i++) {
    printf("%s: khodafez bacheha!\n", names[i]);
    for (int j = i+1; j < n; j++)
      printf("%s: khodafez %s!\n", names[j], names[i]);
  }
  return 0;
}