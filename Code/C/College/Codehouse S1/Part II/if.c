#include<stdio.h>
/*y=x+100 ( 当 x ＜ 20)
y= x ( 当 2 0 ≤ x ≤ 100)
y=x-100 ( 当 x ＞ 100)*/
int main(){
    double x;
    scanf("%lf",&x);
    if (x<20) printf("x=%f, y=%f\n",x,x+100);
    else if (x<=100) printf("x=%f, y=%f",x,x);
    else printf("x=%f, y=%f",x,x-100);
    return 0;
}