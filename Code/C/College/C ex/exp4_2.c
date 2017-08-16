#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 10001
#define N 1000

int array[N], s[MAX-1];

void init(int *a, int n){
    int i;
    srand(time(0));
    for (i = 0;i < n;i++)
        a[i] = rand() % MAX;
}

void sumUp(int *a, int *b){
    int i;
    for (i = 0; i < N; i++)
        b[a[i]]++;
}

void print(int *a, int n){
    int i;
    for (i = 0; i < n; i++)
        if (a[i]) printf("(%d, %d)\n", i, a[i]);
}

int main(){
    init (array, N);
    sumUp(array, s);
    print(s, MAX);
    return 0;
}