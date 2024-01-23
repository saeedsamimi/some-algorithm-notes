#include <stdio.h>

int A[2000][2000];

void generateArray(int);

int main(){
  int n;
  scanf("%d",&n);
  generateArray(n);
  for(int i =0;i<n;i++){
    for(int j = 0;j<n;j++)
      printf("%d ",A[i][j]);
    printf("\n");
  }
}

void generateArray(int n){
  // generate last line
  int row,col,k=1;
  row = n-1;
  for(col = 0;col < n;col++)
    A[row][col] = k++;
  n--;
  char Sw = -1;
  while(n>0){
    // vertical movement
    int minRow = row + Sw * n;
    row+=Sw;
    for(;Sw*(row - minRow) >= 0;row += Sw)
      A[row][col] = k++;
    int minCol = col + Sw * n;
    col += Sw;
    for(;Sw*(col - minCol) >= 0;col += Sw)
      A[row][col] = k++;
    Sw *= -1;
    n--;
  }
}