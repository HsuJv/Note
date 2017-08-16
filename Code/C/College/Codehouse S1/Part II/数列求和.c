#include<stdio.h>
#include<math.h>
int main(){
    double x = 0.0, sum = 0.0, temp;
    long long i = 1, j;
    scanf("%lf", &x);
    for ( ; ; i++){
        temp = pow(x, i);
        for (j = i; j > 1; j--) temp /= j;
        sum += pow(-1, i+1) * temp;
        if (temp < 1E-5) break;
    }
    printf("sum=%.2f\n", sum);
    return 0;
}
