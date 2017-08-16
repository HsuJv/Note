#include<stdio.h>
#include<math.h>

#define P (a + b + c) / 2

void swap(double *a, double *b){
    double t;
    t = *a;
    *a = *b;
    *b = t;
}

int main(){
    double a, b, c, area;
    scanf("%lf%lf%lf", &a, &b, &c);
    if(a > b) swap(&a, &b);
    if(a > c) swap(&a, &c);
    if(b > c) swap(&b, &c);
    if((a < 0) || (a + b <= c))
        printf("Error!Please input again.\n");
    else
        printf("Area=%.3f\n", sqrt(P * (P - a) * (P - b) * (P - c)));
    return 0;
}