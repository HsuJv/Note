#include<stdio.h>
#include<math.h>

int isPrime(int n){
    int k = (int)sqrt(n);
    int i;
    for (i = 2; i <= k; i++)
        if (!(n % i)) return 0;
    return 1;
}

int main(){
    int i, j;
    scanf("%d", &i);
    for (j = 2; j <= (i>>1); j++)
        if(isPrime(j) && isPrime(i - j)){
            printf("%d = %d + %d\n", i, j, i-j);
            break;
        }
    return 0;
}