#include<stdio.h>

int gcd(int a, int b){
    if (!b) return a;
    return gcd(b, a % b);
}

int main(){
    int a, b;
    scanf("%d%d", &a, &b);
    printf("(%d, %d) = %d\n", a, b, gcd(a, b));
    return 0;
}