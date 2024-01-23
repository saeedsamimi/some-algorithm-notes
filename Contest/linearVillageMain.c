#include <stdio.h>

void sort(short int *A,short int n){
    short int i,j,temp;
    for(i=0;i+1<n;i++){
        temp = i;
        for(j=i+1;j<n;j++)
            if(A[j] < A[temp])
                temp = j;
        // use j as temporary variable
        j = A[i];
        A[i] = A[temp];
        A[temp] = j;
    }
}

int main(){
    short int count,R;
    scanf("%hd %hd",&count,&R);
    R*=2;
    short int Arr[20];
    short int max = 0,towerCount = 0;
    for(short int i = 0;i<count;i++)
        scanf("%hd",Arr+i);
    sort(Arr,count);
    for(short int i = 0;i<count;i++)
        if(Arr[i] > max){
            towerCount++;
            max = Arr[i]+R;
        }
    printf("%hd",towerCount);
    return 0;
}
