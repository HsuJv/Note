#include<stdio.h>

int main(){
    int a,b;
    double ave;
    printf("Input two integers:");
    scanf("%d%d",&a,&b);
    ave=(a+b)/2;
    printf("\nThe average of this two integers is :%f\n",ave);
    return 0;
}