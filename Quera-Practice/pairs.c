#include <stdio.h>
#define diff(a,b) ((a>b)?a-b:b-a)

typedef struct{
    int W_Loc,M_Loc;
} pair;

pair array[100000];

int main(){
    int t;
    scanf("%d",&t);
    char tmp[9];
    int loc;
    for(int i = 0;i<t;i++){
        int n;
        scanf("%d",&n);
        n*=2;
        for(int j = 0;j<n;j++){
            scanf("%s",tmp);
            sscanf(tmp+1,"%d",&loc);
            if(tmp[0] == 'W')
                array[loc].W_Loc = j;
            else
                array[loc].M_Loc = j;
        }
        n/=2;
        char count = 0;
        for(int j = 1;j<=n && count < 3;j++)
            if(diff(array[j].M_Loc, array[j].W_Loc) > 1)
                count++;
        printf(count > 2 ? "NO\n":"YES\n");
    }
}