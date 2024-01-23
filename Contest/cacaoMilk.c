#include <stdio.h>

#define max(a,b) a>b?a:b

typedef long long int LL;

int main() {
  int n;
  scanf("%d",&n);
  LL weights[100000];
  LL sum = 0,maxSum = 0;
  for(int i = 0;i<n;i++){
    scanf("%lld",weights+i);
    sum += weights[i];
    if(sum > maxSum)
      maxSum = sum;
  }
  printf("%lld",maxSum);
  return 0;
}