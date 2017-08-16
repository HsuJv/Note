#include<stdio.h>
#define RATE 3.82E-2

double capital;
int i,n;

int main(){
    printf("Plz input the capital and year:");
    scanf("%lf%d",&capital,&n);
    for(;i<n;i++)
        capital*=(1+RATE);
    printf("\nThe deposit is %f.\n",capital);
    return 0;
}