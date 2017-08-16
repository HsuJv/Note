#include<stdio.h>
int main(){
    int year,month,day=0;
    scanf("%d%d",&year,&month);
    switch (month){
        case 1:case 3: case 5 :
        case 7:case 8: case 9 :
        case 10:case 12:day=31;break;
        case 2:day=28;break;
        default:day=30;break;
    }
    if (month==2&&!(year%4)) {
        day++;
        if (!(year%100)&&year%400) day--;
    }
    printf("%d-%d-%d\n",year,month,day);
    return 0;
}