// Created by Saeed - Samimi on 1/22/2024
#include <stdio.h>
#define min(a,b) (a<b)?a:b
#define max(a,b) (a>b)?a:b

typedef struct {
    int s;
    int e;
} interval;

char cmp(interval*,interval*);
void qSort(interval*,int,int);

int main() {
    int n;
    scanf("%d", &n);
    interval vals[100];
    int i;
    for (i = 0; i < n; i++)
        scanf("%d %d", &vals[i].s, &vals[i].e);
    qSort(vals, 0, n - 1);
    int sum = 0;
    for (i = 0; i < n-1; i++)
        if (!cmp(vals + i, vals + i + 1)) {
            // update next interval
            vals[i + 1].s = min(vals[i].s, vals[i + 1].s);
            vals[i + 1].e = max(vals[i].e, vals[i + 1].e);
        }
        else
            sum += vals[i].e - vals[i].s;
    sum += vals[i].e - vals[i].s;
    printf("%d", sum);
    return 0;
}

char cmp(interval* a, interval* b) {
    if (a->e <= b->s) return -1;
    if (a->s >= b->e) return 1;
    return 0;
}

void qSort(interval* A, int start, int end) {
    if (end > start) {
        int i = start, j = end - 1;
        interval temp;
        while (j >= i) {
            if (cmp(A+i,A+end) > 0) {
                temp = A[i];
                A[i--] = A[j];
                A[j--] = temp;
            }
            else
                i++;
        }
        temp = A[end];
        A[end] = A[i];
        A[i] = temp;
        qSort(A, start, i - 1);
        qSort(A, i + 1, end);
    }
}