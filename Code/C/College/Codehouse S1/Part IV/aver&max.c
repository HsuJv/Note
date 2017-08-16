#include<stdio.h>
#include<stdlib.h>

#define f(i, a, b) for(i = a; i < b; i++)

 typedef struct Student {
       int num;
       char name[20];
       int score;
}STU;

int main(){
    STU st[3];
    int i, max = 0;
    double aver = 0;
    
    //freopen("in.txt", "r", stdin);
    f(i, 0, 3){
        scanf("%d%s%d", &st[i].num, st[i].name, &st[i].score);
        aver += st[i].score;
        max = st[max].score > st[i].score ? max : i;
    }
    aver /= 3;
    printf("The average score=%.2f\n", aver);
    printf("The student who has the highest score is:\n");
    printf("%d\t%s\t%d\n", st[max].num, st[max].name, st[max].score);
    return 0;
}