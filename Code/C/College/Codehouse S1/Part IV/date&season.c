#include<stdio.h>

int main(){
    enum Seasons {Spring, Summer, Autumn, Winter} s;
    struct Date{
        int year, month, day;
    }d;
    
    //freopen("in.txt", "r", stdin);
    scanf("%d%d%d", &d.year, &d.month, &d.day);
    switch (d.month / 4){
        case Spring: printf("Now it is Spring\n"); break;
        case Summer: printf("Now it is Summer\n"); break;
        case Autumn: printf("Now it is Autumn\n"); break;
        case Winter: printf("Now it is Winter\n"); break;
    }
    return 0;
}