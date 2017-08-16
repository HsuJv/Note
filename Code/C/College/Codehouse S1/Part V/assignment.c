#include<stdio.h>

#define LEAP_YEAR !(y % 400) || (y % 100 && !(y % 4))

int main(){
    int y;
    scanf("%d", &y);
    if (y < 1000 || y > 9999) printf("Input error!\n");
    else if (LEAP_YEAR) printf("%d is a leap year!\n", y);
    else printf("%d is not a leap year!\n", y);
    return 0;
}