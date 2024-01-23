#include <stdio.h>
#define CAN(a,b) (a->x == -1 || a->y == -1 || b->x == -1 || b->y == -1)

typedef struct {
  int x,y;
} location;

void generateArray(int,int,int,location *,location *);

int main(){
  int n,A,B;
  scanf("%d %d %d",&n,&A,&B);
  location a = {-1,-1},b={-1,-1};//invalid location
  generateArray(n,A,B,&a,&b);
  if(a.x > b.x)
    printf("%d %c\n",a.x - b.x,'L');
  else if(a.x < b.x)
    printf("%d %c\n",b.x - a.x,'R');
  if(a.y> b.y)
    printf("%d %c",a.y - b.y,'U');
  else if(b.y > a.y)
    printf("%d %c",b.y - a.y,'D');
  return 0;
}

void generateArray(int n,int A,int B,location *a,location *b){
  // generate last line
  int row,col,k=1;
  row = n-1;
  for(col = 0;col < n && CAN(a,b);col++,k++)
    if(k == A){
      a->x = col;
      a->y = row;
    }
    else if(k == B){
      b->x = col;
      b->y = row;
    }
  n--,col--;
  char Sw = -1;
  while(n>0 && CAN(a,b)){
    // vertical movement
    int minRow = row + Sw * n;
    row+=Sw;
    for(;Sw*(row - minRow) <= 0 && CAN(a,b);row += Sw,k++)
      if(k == A){
        a->x = col;
        a->y = row;
      }
      else if(k == B){
        b->x = col;
        b->y = row;
      }
    row -= Sw;
    int minCol = col + Sw * n;
    col += Sw;
    for(;Sw*(col - minCol) <= 0 && CAN(a,b);col += Sw,k++)
      if(k == A){
        a->x = col;
        a->y = row;
      }
      else if(k == B){
        b->x = col;
        b->y = row;
      }
    col -= Sw;
    Sw *= -1;
    n--;
  }
}